/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { Injectable, InjectionToken, inject } from '@angular/core';
import * as Core from '@wrapper-wasm';

type CoreLoader = () => Promise<Core.Module>;
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

        this.loading = new Promise((resolve) => {
            this.loader()
                .then(m => {
                    this.module = m;
                    console.log("Core loaded: " + this.module?.Version.getVersionString(), this.module);
                    resolve(m);
                });
        });

        return this.loading;
    }
}

// todo provide worker for complex tasks
