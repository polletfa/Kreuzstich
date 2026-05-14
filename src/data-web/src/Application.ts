/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import Fastify from 'fastify';
import jwt from '@fastify/jwt';
import cookie from '@fastify/cookie';
import { serializerCompiler, validatorCompiler } from 'fastify-type-provider-zod';
import type { ZodTypeProvider } from 'fastify-type-provider-zod';
import type { FastifyInstance, RawServerDefault, FastifyBaseLogger } from 'fastify';
import type { IncomingMessage, ServerResponse } from 'http';

import pgPromise from 'pg-promise';
import type { IDatabase } from 'pg-promise';

import { ConfigService } from './ConfigService';
import { UserService } from './UserService';
import { ThreadListService } from './ThreadListService';
import { Version } from '@version';

export type Database = IDatabase<{}>;
export type Server = FastifyInstance<RawServerDefault, IncomingMessage, ServerResponse, FastifyBaseLogger, ZodTypeProvider>;

export class Application {
    private server: Server;

    // database
    private database: Database;

    // services
    private configService = new ConfigService(); /**< May throw */
    private userService;
    private threadListsService;

    constructor(disableLogs = false) {
        this.database = this.initDatabase();
        this.server = this.initServer(disableLogs);
        this.userService = new UserService(this.server, this.database);
        this.threadListsService = new ThreadListService(this.server, this.database);

        this.routes();
    }

    public get(): Server {
        return this.server;
    }

    /**
     * May throw
     */
    public start(): void {
        this.server.listen({port: this.configService.port, host: '0.0.0.0'}, (err) => {
            if(err) {
                this.server.log.error(err);
                throw new Error('Could not start server.');
            }
        });
    }

    private routes() {
        this.server.get('/version', Version.get);
        this.server.register(this.userService.routes.bind(this.userService), { prefix: '/user' });
        this.server.register(this.threadListsService.routes.bind(this.threadListsService), { prefix: '/threadLists' });
    }

    private initDatabase(): Database {
        return pgPromise()({
            host: this.configService.dbHost,
            port: this.configService.dbPort,
            database: this.configService.dbDatabase,
            user: this.configService.dbUser,
            password: this.configService.dbPassword
        });
    }

    private initServer(disableLogs: boolean): Server {
        // Init HTTP server
        const server = Fastify({
            logger: disableLogs ? false : {
                level: 'info',
                base: null,
                serializers: {
                    req(request) {
                        return {
                            method: request.method,
                            url: request.url,
                            hostname: request.hostname
                        }
                    }
                }
            }
        }).withTypeProvider<ZodTypeProvider>();

        // Setup request validation
        server.setValidatorCompiler(validatorCompiler);
        server.setSerializerCompiler(serializerCompiler);

        // Configure JWT
        server.register(cookie);
        server.register(jwt, {
            secret: this.configService.jwtSecret,
            cookie: {
                cookieName: 'access-token',
                signed: false
            }
        });

        return server;
    }
}
