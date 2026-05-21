/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { Application } from '../src/Application';

export class TestBase {
    constructor() {
        // Init environment
        TestBase.setupEnvironment();

        // Initalize application
        Application.create(/* disableLogs: */ true);
    }

    public static setupEnvironment() {
        process.env.KREUZSTICH_DATA_WEB_PORT=80
        process.env.KREUZSTICH_DATA_WEB_DB_HOST="localhost";
        process.env.KREUZSTICH_DATA_WEB_DB_PORT="5555";
        process.env.KREUZSTICH_DATA_WEB_DB_DB="test";
        process.env.KREUZSTICH_DATA_WEB_DB_USER="test";
        process.env.KREUZSTICH_DATA_WEB_DB_PASSWORD="test";
        process.env.KREUZSTICH_DATA_WEB_JWT_SECRET="test";
    }

    public async setupDatabase(suite: string): Promise<void> {
        const schema = `test_${suite}_${Date.now()}`;
        await Application.instance.database.query(`CREATE SCHEMA ${schema}; SET search_path TO ${schema};`);
        await Application.instance.initDatabaseTables();
        await Application.instance.database.query(`INSERT INTO users(email, name, password) VALUES(
            'test@kreuzstich.art', 'test user', '$2b$10$ZRGfENwLyrvD9/50ozR/Bu572DM53/cyJKgUx08XjC/e9SUcmIRzK')
        ;`);
    }

    public async login(): Promise<string> {
        const loginResp = await Application.instance.server.inject({
            method: 'POST',
            url: '/user/login',
            payload: {
                email: 'test@kreuzstich.art',
                password: 'test',
                persist: false
            }
        });
        return loginResp.cookies[0].value;
    }
}
