import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { firstValueFrom } from 'rxjs';
import { ZodType } from 'zod';

import { environment } from '@environment';
import * as api from '@api/Version';

@Injectable({
    providedIn: 'root',
})
export class DataService {
    constructor(private http: HttpClient) {}

    public async getVersion(): Promise<api.GetVersionResponse> {
        return this.get<api.GetVersionResponse>('version', api.GetVersionResponseSchema);
    }

    private async get<T>(request: string, responseSchema: ZodType): Promise<T> {
        const url = environment.backend + '/' + request;
        const data = await firstValueFrom(this.http.get(url));
        console.log('GET', url, data);
        const res = responseSchema.safeParse(data);
        if(res.success) {
            return res.data as T;
        } else {
            console.error('Invalid response for '+url, res.error);
            throw new Error('Invalid response for '+url);
        }
    }
}
