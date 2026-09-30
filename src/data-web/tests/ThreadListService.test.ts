/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { describe, it, expect, beforeAll } from 'vitest';

import { TestBase } from './TestBase';
import { Application } from '../src/Application';
import * as api from '@datatypes/api/ThreadLists';

const testbase = new TestBase();

beforeAll(async () => {
    await testbase.setupDatabase('ThreadListService');

    await Application.instance.database.query(`INSERT INTO threadlists(user_id, name) VALUES (1, 'user list');`);
    await Application.instance.database.query(`INSERT INTO threads(list_id,name,color) VALUES
        (2, 'black', '000000'),
        (2, 'white', 'ffffff')
    ;`);
});

describe('ThreadListService', () => {
    it('GET /threadLists, not logged in', async () => {
        const response = await Application.instance.server.inject({
            method: 'GET',
            url: '/threadLists'
        });

        expect(response.statusCode).toBe(200);
        expect(response.json().data.length).toEqual(1);
        expect(response.json().data[0].name).toEqual('DMC');
        expect(response.json().data[0].threads.length).toEqual(447);
    });

    it('GET /threadLists, logged in', async () => {
        const response = await Application.instance.server.inject({
            method: 'GET',
            url: '/threadLists',
            cookies: { 'access-token': await testbase.login() }
        });

        expect(response.statusCode).toBe(200);
        expect(response.json().data.length).toEqual(2);
        expect(response.json().data.map(i => i.name)).toEqual(['DMC', 'user list']);
    });
});

describe('ThreadListService, database error', () => {
    beforeAll(async () => {
        await Application.instance.database.query('DROP TABLE threads CASCADE;');
    });

    it('GET /threadLists', async () => {
        const response = await Application.instance.server.inject({
            method: 'GET',
            url: '/threadLists'
        });

        expect(response.statusCode).toBe(500);
        expect(response.json()).toEqual({success: false, error: "relation \"threads\" does not exist"});
    });
});
