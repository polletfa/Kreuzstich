import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { firstValueFrom } from 'rxjs';
import { ZodType } from 'zod';

import * as api from '@datatypes/api/Version';

/**
 * Service to communicate with the data-web component (backend)
 */
@Injectable({
    providedIn: 'root',
})
export class DataService {
    constructor(private http: HttpClient) {}

    public async getVersion(): Promise<api.GetVersionResponse> {
        return this.get('version', api.GetVersionResponseSchema);
    }

    /**
     * Generic method for GET
     */
    public async get<T>(request: string, responseSchema: ZodType): Promise<T> {
        const url = '/api/' + request;
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

    /**
     * Generic method for POST
     */
    public async post<R, T>(request: string, requestBody: R, responseSchema: ZodType): Promise<T> {
        const url = '/api/' + request;
        const data = await firstValueFrom(this.http.post(url, requestBody));
        console.log('POST', url, data);
        const res = responseSchema.safeParse(data);
        if(res.success) {
            return res.data as T;
        } else {
            console.error('Invalid response for '+url, res.error);
            throw new Error('Invalid response for '+url);
        }
    }
}
