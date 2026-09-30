/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import type { FastifyReply } from 'fastify';

import { Helpers } from './Helpers';
import type { Server, Database } from './Application';
import type { User } from '@datatypes/api/User';
import { AuthHelper } from './AuthHelper';
import * as api from '@datatypes/api/ThreadLists';
import * as db from '@datatypes/db';

import getThreadLists from '@sql/getThreadLists.sql';
import getUserThreadLists from '@sql/getThreadLists.sql' with { user: 'true' };

/**
 * Manage thread lists.
 */
export class ThreadListService {
    constructor(private server: Server, private db: Database) {}

    /**
     * Register routes for the service
     */
    public async routes(server: Server) {
        server.get('/', { onRequest: AuthHelper.authenticateNoFail }, (request, response) => this.getLists(request.user as User|undefined, response));
    }

    /**
     * Get all lists accessible to the specified user
     */
    private async getLists(user: User|undefined, response: FastifyReply): Promise<api.GetThreadListsResponse> {
        try {
            this.server.log.info(user);
            this.server.log.info(getUserThreadLists);
            const res = user
                ? await this.db.manyOrNone<db.ThreadListFull>(getUserThreadLists, [user.id])
                : await this.db.manyOrNone<db.ThreadListFull>(getThreadLists);
            return {success: true, data: res};
        } catch(error) {
            this.server.log.error(Helpers.errorToString(error));
            response.code(500);
            return {success: false, error: Helpers.errorToString(error)};
        }
    }
}
