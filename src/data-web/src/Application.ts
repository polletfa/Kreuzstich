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
import type { FastifyInstance, FastifyReply, FastifyRequest, RawServerDefault, FastifyBaseLogger } from 'fastify';
import type { IncomingMessage, ServerResponse } from 'http';

import pino from 'pino';
import pinoPretty from 'pino-pretty';
import FileStreamRotator from 'file-stream-rotator';
import type { StreamEntry } from 'pino';

import pgPromise from 'pg-promise';
import type { IDatabase } from 'pg-promise';

import { ConfigService } from './ConfigService';
import { UserService } from './UserService';
import { Version } from '@version';

export type Database = IDatabase<{}>;
export type Server = FastifyInstance<RawServerDefault, IncomingMessage, ServerResponse, FastifyBaseLogger, ZodTypeProvider>;
export type Authenticator = (request: FastifyRequest, response: FastifyReply) => Promise<void>;

export class Application {
    private server: Server;

    // database
    private database: Database;

    // services
    private configService = new ConfigService(); /**< May throw */
    private userService;

    constructor(disableLogs = false) {
        this.database = this.initDatabase();
        this.server = this.initServer(disableLogs);
        this.userService = new UserService(this.server, this.authenticate.bind(this), this.database);

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
        // Logger
        const logStreams: StreamEntry[] = [
            { stream: pinoPretty({translateTime: "SYS:standard"}) }
        ];
        if(this.configService.logDir) {
            logStreams.push({ stream: FileStreamRotator.getStream({
                filename: this.configService.logDir + '/data-web.%DATE%.log',
                frequency: 'daily',
                date_format: 'YYYY-MM-DD',
                max_logs: '90d'
            })});
        }
        const loggers = pino.multistream(logStreams);

        // Init HTTP server
        const server = Fastify({
            logger: disableLogs ? false : {
                level: 'info',
                stream: loggers
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

    private async authenticate(request: FastifyRequest, response: FastifyReply): Promise<void> {
        try {
            await request.jwtVerify();
        } catch (err) {
            response.code(401).send({ error: 'Unauthorized' });
        }
    }
}
