/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import Fastify from 'fastify';
import pinoPretty from 'pino-pretty';
import FileStreamRotator from 'file-stream-rotator';
import pino from 'pino';

import type { FastifyInstance } from 'fastify';
import type { StreamEntry } from 'pino';

import { ConfigService } from './ConfigService';
import { Version } from '@version';

export class Server {
    private config = new ConfigService(); /**< can throw */
    private server: FastifyInstance;

    constructor(disableLogs = false) {
        // Logger
        const logStreams: StreamEntry[] = [
            { stream: pinoPretty({translateTime: "SYS:standard"}) }
        ];
        if(this.config.logDir) {
            logStreams.push({ stream: FileStreamRotator.getStream({
                filename: this.config.logDir + '/data-web.%DATE%.log',
                frequency: 'daily',
                date_format: 'YYYY-MM-DD',
                max_logs: '365d'
            })});
        }
        const loggers = pino.multistream(logStreams);

        // Init HTTP server
        this.server = Fastify({
            logger: disableLogs ? false : {
                level: 'info',
                stream: loggers
            }
        });

        // Routing
        this.server.get('/version', async () => {
            return { versionString: Version.getVersionString() };
        });
    }

    public get(): FastifyInstance {
        return this.server;
    }

    /**
     * May throw
     */
    public start(): void {
        this.server.listen({port: this.config.port, host: '0.0.0.0'}, (err) => {
            if(err) {
                this.server.log.error(err);
                throw new Error('Could not start server.');
            }
        });
    }
}
