/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import type { Server, Database } from './Application';
import type { User } from '@datatypes/api/User';
import { AuthHelper } from './AuthHelper';
import * as api from '@datatypes/api/ThreadLists';
import * as db from '@datatypes/db';

export class ThreadListService {
    constructor(private server: Server, private db: Database) {}

    /**
     * Register routes for the service
     */
    public async routes(server: Server) {
        server.get('/', { onRequest: AuthHelper.authenticateNoFail }, (request) => this.getLists(request.user as User));
    }

    private async getLists(user: User): Promise<api.GetThreadListsResponse> {
        try {
            const res = user
                ? await this.db.manyOrNone<db.ThreadList>('SELECT * FROM threadlists WHERE user_id = $1 OR user_id IS NULL;', [user.id])
                : await this.db.manyOrNone<db.ThreadList>('SELECT * FROM threadlists WHERE user_id IS NULL;');
            return {success: true, data: res};
        } catch(error) {
            this.server.log.error('Database error: ${error.message}');
        }
        return {success: false};
    }
}
