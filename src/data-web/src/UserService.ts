/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import type { FastifyReply } from 'fastify';
import bcrypt from 'bcryptjs';

import type { Server, Authenticator, Database } from './Application';
import * as api from '@api/User';
import * as db from '@db';

export class UserService {
    constructor(private server: Server, private authenticate: Authenticator, private db: Database) {}

    /**
     * Register routes for the service
     */
    public async routes(server: Server) {
        // public
        server.post('/login', { schema: { body: api.PostUserLoginRequestSchema } }, (request, response) => this.login(request.body, response));
        server.get('/logout', (_, response) => this.logout(response));

        // protected
        server.get('/status', { onRequest: this.authenticate }, (request) => request.user);
    }

    private async login(request: api.PostUserLoginRequest, response: FastifyReply): Promise<api.PostUserLoginResponse> {
        try {
            const user = await this.db.oneOrNone<db.User>('SELECT * FROM users WHERE email = $1;', [request.email]);
            if(user && await bcrypt.compare(request.password, user.password)) {
                const { password, ...tokenPayload} = user;
                const token = await response.jwtSign(tokenPayload, { expiresIn: request.persist ? '30d' : '1d' });
                response.setCookie('access-token', token, {
                    httpOnly: true,
                    secure: true,
                    sameSite: 'strict',
                    path: '/',
                    maxAge: request.persist ? 60*60*24*30 : undefined
                });
                return tokenPayload;
            }
        } catch(error) {
            this.server.log.error(error);
        }
        return undefined;
    }

    private async logout(response: FastifyReply): Promise<api.GetUserLogoutResponse> {
        response.clearCookie('access-token');
        return {success: true};
    }
}
