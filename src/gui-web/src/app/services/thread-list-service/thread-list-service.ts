import { Injectable } from '@angular/core';

import type * as Core from '@wrapper-wasm';
import { DataService } from '@services/data-service/data-service';
import { CoreService } from '@services/core-service/core-service';

import * as api from '@datatypes/api/ThreadLists';
import * as db from '@datatypes/db';

/**
 * Service to manage threadlists
 */
@Injectable({
    providedIn: 'root',
})
export class ThreadListService {
    // TODO: for now, we just load the lists and never modify them. But later if lists are
    //       replaced by new one, don't forget to delete the previous lists first!
    private lists: Core.ThreadList[] | undefined = undefined;

    constructor(
        private coreService: CoreService,
        private dataService: DataService
    ) {
    }

    public async get(): Promise<Core.ThreadList[]|undefined> {
        if(this.lists) {
            return this.lists;
        } else {
            try {
                const res = await this.dataService.get<api.GetThreadListsResponse>('threadLists', api.GetThreadListsResponseSchema);
                if(res.success && res.data) {
                    this.lists = await this.createWASMObjects(res.data);
                    return this.lists;
                } else {
                    throw new Error('Failed to retrieve threadlists');
                }
            } catch(error) {
                console.error(error);
                return undefined;
            }
        }
    }

    /**
     * Create threadlists for the WASM core library.
     */
    private async createWASMObjects(lists: db.ThreadListFull[]): Promise<Core.ThreadList[]> {
        const core = await this.coreService.get();
        const wasmLists: Core.ThreadList[] = [];

        for(const list of lists) {
            const threads = list.threads.map(t => new core.Thread(t.name, t.color));
            wasmLists.push(new core.ThreadList(list.name, threads));
            threads.forEach(t => t.delete());
        }
        return wasmLists;
    }
}
