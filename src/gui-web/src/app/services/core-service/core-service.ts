/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { Injectable, InjectionToken, inject } from '@angular/core';
import * as Core from '@wrapper-wasm';
import { Version } from '@version';

type CoreLoader = (locateFile?: (file:string, prefix: string)=>string) => Promise<Core.Module>;
export const CORE_LOADER = new InjectionToken<CoreLoader>('CORE_LOADER');

/**
 * Service to access the core library
 */
@Injectable({
    providedIn: 'root',
})
export class CoreService {
    private loader = inject(CORE_LOADER);
    private module?: Core.Module;
    private loading?: Promise<Core.Module>;

    public async get(): Promise<Core.Module> {
        if (this.module) return Promise.resolve(this.module);
        if (this.loading) return this.loading;

        this.loading = new Promise((resolve, reject) => {
            this.loader((path: string, prefix: string) => {
                let modifiedPath = path;
                if(path.endsWith('.wasm')) {
                    modifiedPath = path.slice(0, -5) + '.' + Version.BUILD_TIME.replace(/:/g, '-') + '.wasm';
                }
                console.log(`${prefix}${modifiedPath}`);
                return `${prefix}${modifiedPath}`;
            }).then(m => {
                this.module = m;
                console.log("Core loaded: " + this.module?.Version.getVersionString(), this.module);
                resolve(m);
            }).catch(() => {
                reject("Unable to load core library.");
            });
        });

        return this.loading;
    }
}

// todo provide worker for complex tasks
