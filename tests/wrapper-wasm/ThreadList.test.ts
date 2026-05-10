/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

// Note: we only check the bindings, not the functionality, which is tested directly in the core component.

import { describe, it, expect, beforeAll, beforeEach, afterEach } from 'vitest';
import * as Core from './build/wrapper-wasm';

let core: Core.Module;

beforeAll(async () => {
    core = await Core.load();
});

describe('ThreadList', () => {
    let list: Core.ThreadList;

    beforeEach(() => {
        const threads: Core.Thread[] = [
            new core.Thread("black", "000000"),
            new core.Thread("red", "ff0000"),
            new core.Thread("white", "ffffff")
        ];
        list = new core.ThreadList(threads);
        for(const thr of threads) {
            thr.delete();
        }
    });

    afterEach(() => {
        if(!list.isDeleted()) {
            list.delete();
        }
    });

    it('delete/isDeleted', () => {
        expect(list.isDeleted()).toBe(false);
        list.delete();
        expect(list.isDeleted()).toBe(true);
    });

    it('Symbol.dispose', () => {
        let ref;
        {
            using newList = new core.ThreadList([]);
            ref = newList
        }
        expect(ref.isDeleted()).toBe(true); // deleted when newList went out of scope
    });

    it('get', () => {
        const threads = list.get('HSL', 'ASC');
        expect(threads.length).toBe(3);
        expect(threads[0].name()).toBe('black');
        expect(threads[1].name()).toBe('white');
        expect(threads[2].name()).toBe('red');

        expect(() => { threads[0].delete(); }).toThrow();
    });

    it('findClosest', () => {
        const res = list.findClosest({red: 0xdd, green: 0, blue: 0, alpha: 0xff}, 'CIEDE2000');
        expect(res?.name()).toBe('red');
        expect(() => { res?.delete(); }).toThrow();
    });

    it('findClosestInUse, none in use', () => {
        const res = list.findClosestInUse({red: 0xdd, green: 0, blue: 0, alpha: 0xff}, 'CIEDE2000');
        expect(res).toBe(undefined); // none in use
    });

    it('findClosestInUse, some in use', () => {
        const usage = list.usage();
        const black = usage.find(u => u.thread.name() === 'black');
        if(black) {
            black.count=1;
        }
        list.setUsage(usage);

        const res = list.findClosestInUse({red: 0xdd, green: 0, blue: 0, alpha: 0xff}, 'CIEDE2000');
        expect(res?.name()).toBe('black'); // only one in use, so closest
        expect(() => { res?.delete(); }).toThrow();
    });

    it('findThread, not found', () => {
        const res = list.findThread({red: 0xfe, green: 0, blue: 0, alpha: 0xff});
        expect(res).toBe(undefined);
    });

    it('findThread, found', () => {
        const res = list.findThread({red: 0xff, green: 0, blue: 0, alpha: 0xff});
        expect(res?.name()).toBe('red');
        expect(() => { res?.delete(); }).toThrow();
    });

    it('usage, setUsage, updateUsage', () => {
        const threads = list.get('HSL', 'ASC');
        const usage = list.usage();
        for(const u of usage) {
            if(u.thread.name() == 'black') {
                u.count = 10;
            } else if(u.thread.name() == 'white') {
                u.count = 5;
            } else if(u.thread.name() == 'red') {
                u.count = 8;
            }
        }
        list.setUsage(usage);

        list.updateUsage(threads[0], threads[2], 3);

        const newUsage = list.usage();
        expect(newUsage.length).toBe(3);

        expect(newUsage[0].thread.name()).toBe('red');
        expect(newUsage[0].count).toBe(11);
        expect(() => { newUsage[0].thread.delete(); }).toThrow();

        expect(newUsage[1].thread.name()).toBe('black');
        expect(newUsage[1].count).toBe(7);
        expect(() => { newUsage[1].thread.delete(); }).toThrow();

        expect(newUsage[2].thread.name()).toBe('white');
        expect(newUsage[2].count).toBe(5);
        expect(() => { newUsage[2].thread.delete(); }).toThrow();
    });
});
