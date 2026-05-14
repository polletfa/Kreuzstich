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

// import { Injectable, NgZone, OnDestroy } from '@angular/core';

// @Injectable({ providedIn: 'root' })
// export class WasmWorkerService implements OnDestroy {
//     private worker: Worker | null = null;
//     private pending = new Map<string, (result: any) => void>();
//     private ready: Promise<void>;
//     private resolveReady!: () => void;

//     constructor(private zone: NgZone) {
//         this.ready = new Promise(r => this.resolveReady = r);
//         this.initWorker();
//     }

//     private initWorker() {
//         this.worker = new Worker(
//             new URL('./wasm.worker', import.meta.url),
//             { type: 'module' }
//         );

//         this.worker.onmessage = ({ data }) => {
//             if (data.type === 'READY') {
//                 this.resolveReady();
//                 return;
//             }
//             // resolve pending promise for this message type
//             const resolve = this.pending.get(data.type);
//             if (resolve) {
//                 this.pending.delete(data.type);
//                 // run inside Angular zone so change detection fires
//                 this.zone.run(() => resolve(data.result));
//             }
//         };

//         this.worker.postMessage({ type: 'INIT' });
//     }

//     private async send<T>(outType: string, replyType: string, payload?: any): Promise<T> {
//         await this.ready;
//         return new Promise(resolve => {
//             this.pending.set(replyType, resolve);
//             this.worker!.postMessage({ type: outType, payload });
//         });
//     }

//     // --- Typed public API ---

//     add(a: number, b: number): Promise<number> {
//         return this.send<number>('ADD', 'ADD_RESULT', { a, b });
//     }

//     myClassGetX(x: number): Promise<number> {
//         return this.send<number>('MY_CLASS_GET_X', 'MY_CLASS_GET_X_RESULT', { x });
//     }

//     ngOnDestroy() {
//         this.worker?.terminate();
//     }
// }
