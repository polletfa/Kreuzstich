import { TestBed } from '@angular/core/testing';

import { CORE_LOADER } from '@services/core-service/core-service';
import { mockCore } from '@tests/core.mockup';
import { ThreadListService } from './thread-list-service';

describe('ThreadListService', () => {
    let service: ThreadListService;

    beforeEach(() => {
        TestBed.configureTestingModule({
            providers: [
                { provide: CORE_LOADER, useValue: () => Promise.resolve(mockCore) }
            ]
        });
        service = TestBed.inject(ThreadListService);
    });

    it('should be created', () => {
        expect(service).toBeTruthy();
    });
});
