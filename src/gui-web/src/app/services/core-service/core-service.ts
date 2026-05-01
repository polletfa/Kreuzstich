import { Injectable } from '@angular/core';

@Injectable({
    providedIn: 'root',
})
export class CoreService {
    private module?: Core;
    private loading?: Promise<Core>;

    public async get(): Promise<Core> {
        if (this.module) return Promise.resolve(this.module);
        if (this.loading) return this.loading;

        this.loading = new Promise((resolve, reject) => {
            const script = document.createElement('script');
            script.src = 'core.js';
            script.onload = () => {
                CoreModule({ locateFile: (file: string) => `${file}` })
                    .then(m => {
                        this.module = m;
                        console.log("Core loaded: " + this.module?.Version.getVersionString(), this.module);
                        resolve(m);
                    })
                    .catch(reject);
            };
            script.onerror = reject;
            document.body.appendChild(script);
        });

        return this.loading;
    }
}
