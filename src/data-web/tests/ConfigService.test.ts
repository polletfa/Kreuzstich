/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { describe, it, expect, beforeEach } from 'vitest';

import { TestBase } from './TestBase';
import { ConfigService } from '../src/ConfigService';

describe('ConfigService', () => {
    beforeEach(() => {
        TestBase.setupEnvironment(); // restore default values for envvars
    })

    it('All set', () => {
        const service = new ConfigService();
        expect(service.port).toBe(80);
        expect(service.dbHost).toBe('localhost');
        expect(service.dbPort).toBe(5555);
        expect(service.dbDatabase).toBe('test');
        expect(service.dbUser).toBe('test');
        expect(service.dbPassword).toBe('test');
        expect(service.jwtSecret).toBe('test');
    });

    it('port unset', () => {
        delete process.env.KREUZSTICH_DATA_WEB_PORT;
        expect(() => {
            const service = new ConfigService();
        }).toThrow();
    });

    it('port not a number', () => {
        process.env.KREUZSTICH_DATA_WEB_PORT = 'test';
        expect(() => {
            const service = new ConfigService();
        }).toThrow();
    });

    it('dbHost unset', () => {
        delete process.env.KREUZSTICH_DATA_WEB_DB_HOST;
        expect(() => {
            const service = new ConfigService();
        }).toThrow();
    });

    it('dbPort unset', () => {
        delete process.env.KREUZSTICH_DATA_WEB_DB_PORT;
        let service: ConfigService;
        expect(() => {
            service = new ConfigService();
        }).not.toThrow();
        expect(service.dbPort).toBe(5432);
    });

    it('dbPort not a number', () => {
        process.env.KREUZSTICH_DATA_WEB_DB_PORT = 'test';
        expect(() => {
            const service = new ConfigService();
        }).toThrow();
    });

    it('dbDatabse unset', () => {
        delete process.env.KREUZSTICH_DATA_WEB_DB_DB;
        expect(() => {
            const service = new ConfigService();
        }).toThrow();
    });

    it('dbUser unset', () => {
        delete process.env.KREUZSTICH_DATA_WEB_DB_USER;
        expect(() => {
            const service = new ConfigService();
        }).toThrow();
    });

    it('dbPassword unset', () => {
        delete process.env.KREUZSTICH_DATA_WEB_DB_PASSWORD;
        expect(() => {
            const service = new ConfigService();
        }).toThrow();
    });

    it('jwtSecret unset', () => {
        delete process.env.KREUZSTICH_DATA_WEB_JWT_SECRET;
        expect(() => {
            const service = new ConfigService();
        }).toThrow();
    });
});
