import { TestBed } from '@angular/core/testing';
import { HttpClient } from '@angular/common/http';
import { of, throwError } from 'rxjs';
import { z } from 'zod';

import { DataService } from './data-service';

class HttpClientMock {
    error = false;

    get = vi.fn().mockImplementation((url) => {
        if(this.error) {
            return throwError({success: !this.error, url: url});
        } else {
            return of({success: !this.error, url: url});
        }
    });
    post = vi.fn().mockImplementation((url, request) => {
        if(this.error) {
            return throwError({success: !this.error, url, request});
        } else {
            return of({success: !this.error, url, request});
        }
    });
}

describe('DataService', () => {
    const testObjectSchema = z.object({
        success: z.boolean(),
        url: z.string(),
        request: z.any().optional()
    });
    const wrongObjectSchema = z.object({wrongSchema: z.string()});
    let service: DataService;
    let httpClientMock: HttpClientMock;

    beforeEach(() => {
        httpClientMock = new HttpClientMock();
        TestBed.configureTestingModule({
            providers: [
                { provide: HttpClient, useValue: httpClientMock },
            ]
        });
        service = TestBed.inject(DataService);
    });

    it('should be created', () => {
        expect(service).toBeTruthy();
    });

    it('getVersion', async () => {
        await expect(async () => {
            await service.getVersion();
        }).rejects.toThrow(new Error('Invalid response for /api/version')); // throws because the mockup doesn't return a GetVersionResponse object
    });

    it('get, valid object', async () => {
        const res = await service.get('test', testObjectSchema);
        expect(res).toEqual({success: true, url: '/api/test'});
    });

    it('get, invalid object', async () => {
        await expect(async () => {
            await service.get('test', wrongObjectSchema);
        }).rejects.toThrow(new Error('Invalid response for /api/test'));
    });

    it('get, error', async () => {
        httpClientMock.error = true;
        await expect(async () => {
            await service.get('test', testObjectSchema);
        }).rejects.toThrow({success: false, url: '/api/test'});
    });

    it('post, valid object', async () => {
        const res = await service.post('test', {test: true}, testObjectSchema);
        expect(res).toEqual({success: true, url: '/api/test', request: {test: true}});
    });

    it('post, invalid object', async () => {
        await expect(async () => {
            await service.post('test', {test: true}, wrongObjectSchema);
        }).rejects.toThrow(new Error('Invalid response for /api/test'));
    });

    it('post, error', async () => {
        httpClientMock.error = true;
        await expect(async () => {
            await service.post('test', {test: true}, testObjectSchema);
        }).rejects.toThrow({success: false, url: '/api/test', request: {test: true}});
    });
});

// todo
