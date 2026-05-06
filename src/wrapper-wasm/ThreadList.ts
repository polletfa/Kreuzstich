/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import type * as wasm from './wrapper-wasm';
import { Thread } from './Thread';
import { ColorSpace } from './ColorSpace';

export namespace ThreadList {
    export type SortBy = "HLS"|"HSL"|"Name";
    export type SortOrder = "ASC"|"DESC";

    export type UsageCount = {
        thread: ThreadRef;
        count: number;
    }[];
}


/**
 * Used for references to Thread that should not be deleted (no ownership)
 */
export type ThreadRef = Omit<Thread, 'delete'|'isDeleted'>;

export class ThreadList {
    constructor(private obj: wasm.ThreadList, private core: wasm.MainModule) {}

    delete() { this.obj.delete(); }
    isDeleted(): boolean { return this.obj.isDeleted(); }
    [Symbol.dispose]() { this.delete(); }

    get(sortBy: ThreadList.SortBy, sortOrder: ThreadList.SortOrder): ThreadRef[] {
        using list = this.obj.get(sortBy, sortOrder);
        const outList: ThreadRef[] = [];
        for(let i = 0; i < list.size(); ++i) {
            const item = list.get(i);
            if(item) {
                outList.push(new Thread(item));
            }
        }
        return outList;
    }
    findClosest(color: ColorSpace.ColorRGBA, algo: ColorSpace.DistanceAlgo): ThreadRef|undefined {
        const res = this.obj.findClosest(color, algo);
        return res ? new Thread(res) : undefined;
    }
    findClosestInUse(color: ColorSpace.ColorRGBA, algo: ColorSpace.DistanceAlgo): ThreadRef|undefined {
        const res = this.obj.findClosestInUse(color, algo);
        return res ? new Thread(res) : undefined;
    }
    findThread(color: ColorSpace.ColorRGBA): ThreadRef|undefined {
        const res = this.obj.findThread(color);
        return res ? new Thread(res) : undefined;
    }
    usage(): ThreadList.UsageCount {
        using list = this.obj.usage();
        const outList: ThreadList.UsageCount = [];
        for(let i = 0; i < list.size(); ++i) {
            const item = list.get(i);
            if(item) {
                outList.push({thread: new Thread(item.thread), count: item.count});
            }
        }
        return outList;
    }
    setUsage(usage: ThreadList.UsageCount) {
        using list = new this.core.ThreadList_UsageCountVector();
        for(const item of usage) {
            list.push_back({
                thread: (item.thread.wasm() as any).$$.ptr,
                count: item.count
            });
        }
        this.obj.setUsage(list)
    }
    updateUsage(original: Thread, replacement: Thread, count: number) {
        this.obj.updateUsage(original.wasm(), replacement.wasm(), count);
    }
}

export interface ThreadListConstructor {
    new(threads: Thread[]): ThreadList
};

export function ThreadListConstructor(core: wasm.MainModule): ThreadListConstructor {
    return class extends ThreadList {
        constructor(threads: Thread[]) {
            using vector = new core.ThreadVector();
            for(const thread of threads) {
                vector.push_back(thread.wasm());
            }
            super(new core.ThreadList(vector), core);
        }
    };
}
