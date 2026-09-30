/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { TestBed } from '@angular/core/testing';
import { CoreService } from './core-service';
import { CORE_LOADER } from '@services/core-service/core-service';

const mockCore = {
    Version: {
        getVersionString: vi.fn().mockReturnValue('test')
    }
};
const mockCoreLoader = vi.fn().mockReturnValue(Promise.resolve(mockCore));

describe('CoreService', () => {
    let service: CoreService;

    beforeEach(() => {
        TestBed.configureTestingModule({
            providers: [
                { provide: CORE_LOADER, useValue: mockCoreLoader }
            ]
        });
        service = TestBed.inject(CoreService);

        vi.clearAllMocks();
    });

    it('should be created', () => {
        expect(service).toBeTruthy();
    });

    it('get', async () => {
        const core = await service.get();
        expect(core.Version.getVersionString()).toBe('test');
    });

    it('get: core is loaded only once', async () => {
        expect(mockCoreLoader).toHaveBeenCalledTimes(0);

        await service.get();
        expect(mockCoreLoader).toHaveBeenCalledTimes(1);

        await service.get();
        expect(mockCoreLoader).toHaveBeenCalledTimes(1); // still only once
    });
});
