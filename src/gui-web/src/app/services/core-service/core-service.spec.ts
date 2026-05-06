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
        getVersionString: vi.fn().mockReturnValue('mocked')
    }
};

describe('CoreService', () => {
    let service: CoreService;

    beforeEach(() => {
        TestBed.configureTestingModule({
            providers: [
                { provide: CORE_LOADER, useValue: () => Promise.resolve(mockCore) }
            ]
        });
        service = TestBed.inject(CoreService);
    });

    it('should be created', () => {
        expect(service).toBeTruthy();
    });

    it('get', () => {
        service.get();
    });

    // todo test get?
});
