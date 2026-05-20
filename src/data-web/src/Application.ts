/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

// HTTP
import Fastify from 'fastify';
import jwt from '@fastify/jwt';
import cookie from '@fastify/cookie';
import { serializerCompiler, validatorCompiler } from 'fastify-type-provider-zod';
import type { ZodTypeProvider } from 'fastify-type-provider-zod';
import type { FastifyInstance, RawServerDefault, FastifyBaseLogger } from 'fastify';
import type { IncomingMessage, ServerResponse } from 'http';

// Database
import pgPromise from 'pg-promise';
import type { IDatabase } from 'pg-promise';

// Services
import { ConfigService } from './ConfigService';
import { UserService } from './UserService';
import { ThreadListService } from './ThreadListService';
import { Version } from '@version';

// SQL
import createUsers from '@sql/create.users.sql';
import createThreadlists from '@sql/create.threadlists.sql';
import createThreads from '@sql/create.threads.sql';
import doesThreadListExist from '@sql/doesThreadlistexist.sql';

// Built-in threadlists
import dmc from '@threadlists/DMC.sql';

export type Database = IDatabase<{}>;
export type Server = FastifyInstance<RawServerDefault, IncomingMessage, ServerResponse, FastifyBaseLogger, ZodTypeProvider>;

/**
 * Main class.
 * Load services and launch HTTP server
 */
export class Application {
    private static _instance: Application|undefined = undefined; /**< Singleton instance */

    private _server: Server; /**< HTTP server */
    private _database: Database; /**< Database connection */

    // services
    private configService = new ConfigService(); /**< May throw */
    private userService;
    private threadListsService;

    /**
     * Get singleton instance - Create (with default parameters) if necessary
     */
    public static get instance(): Application {
        Application._instance = Application._instance ? Application._instance : new Application();
        return Application._instance;
    }

    /**
     * Create singleton instance with parameters - Throws if the instance has already been created.
     * Only required if you want to use non-default values for the parameters, otherwise simply use Application.instance instead.
     */
    public static create(disableLogs = false): Application {
        if(Application._instance) {
            throw new Error('Application has already been created.');
        }
        Application._instance = new Application(disableLogs);
        return Application._instance;
    }

    private constructor(disableLogs = false) {
        // Open database
        this._database = this.connectDatabase();

        // Initialize HTTP server
        this._server = this.initServer(disableLogs);

        // Load services
        this.userService = new UserService(this.server, this.database);
        this.threadListsService = new ThreadListService(this.server, this.database);

        // Create HTTP routes
        this.routes();
    }

    /**
     * Get HTTP server instance
     */
    public get server(): Server {
        return this._server;
    }

    /**
     * Get database connection
     */
    public get database(): Database {
        return this._database;
    }

    /**
     * Create database tables if they don't exist
     */
    public async initDatabaseTables(): Promise<void> {
        await this.database.query(createUsers);
        await this.database.query(createThreadlists);
        await this.database.query(createThreads);

        // built-in threadlists
        await this.installBuiltInThreadList('DMC', dmc);
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

    /**
     * Install a built-in threadlist, if it doesn't exist yet
     */
    private async installBuiltInThreadList(name: string, sql: string): Promise<void> {
        try {
            await this.database.one(doesThreadListExist, [name]);
        } catch {
            this.server.log.info(`Install built-in list ${name}`);
            await this.database.query(sql);
        }
    }

   /**
     * Create HTTP routes
     */
    private routes() {
        this.server.get('/version', Version.get);
        this.server.register(this.userService.routes.bind(this.userService), { prefix: '/user' });
        this.server.register(this.threadListsService.routes.bind(this.threadListsService), { prefix: '/threadLists' });
    }

    /**
     * Connect to database
     */
    private connectDatabase(): Database {
        return pgPromise()({
            host: this.configService.dbHost,
            port: this.configService.dbPort,
            database: this.configService.dbDatabase,
            user: this.configService.dbUser,
            password: this.configService.dbPassword
        });
    }

     /**
     * Create HTTP server
     */
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
