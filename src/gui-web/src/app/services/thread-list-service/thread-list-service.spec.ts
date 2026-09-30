import { TestBed } from '@angular/core/testing';

import { CORE_LOADER } from '@services/core-service/core-service';
import { mockCore } from '@tests/core.mockup';
import { ThreadListService } from './thread-list-service';

import { DataService } from '@services/data-service/data-service';

const lists = [
    {id: 1, user_id: null, name: 'list', threads: [
        {id: 1, list_id: 1, name: 'thread1', color: '000000'},
        {id: 2, list_id: 1, name: 'thread2', color: '111111'}
    ]}
];

class DataServiceMock {
    constructor(public response: boolean|'error') {}

    private async mockResponse() {
        switch(this.response) {
            case true:
                return {success: true, data: lists};
            case false:
                return {success: false, error: 'Error'};
            case 'error':
                throw new Error('invalid response');
        }
    }

    get = vi.fn().mockImplementation(async () => {
        return this.mockResponse();
    });
}

describe('ThreadListService', () => {
    let service: ThreadListService;
    let dataServiceMock: DataServiceMock;

    beforeEach(() => {
        dataServiceMock = new DataServiceMock(true);
        TestBed.configureTestingModule({
            providers: [
                { provide: CORE_LOADER, useValue: () => Promise.resolve(mockCore) },
                { provide: DataService, useValue: dataServiceMock }
            ]
        });
        service = TestBed.inject(ThreadListService);
        vi.clearAllMocks();
    });

    it('should be created', () => {
        expect(service).toBeTruthy();
    });

    it('get, success', async () => {
        const res = await service.get();
        expect(res).not.toBe(undefined);
        if(res) {
            expect(res.length).toBe(1);
            expect(res[0] instanceof mockCore.ThreadList).toBe(true);
            const threads = res[0].get('Name', 'ASC');
            expect(threads.length).toBe(2);
            threads.forEach(t => expect(t instanceof mockCore.Thread).toBe(true));
        }
    });

    it('get, failure', async () => {
        dataServiceMock.response = false; // valid response, but success = false
        const res = await service.get();
        expect(res).toBe(undefined);
    });

    it('get, HTTP error', async () => {
        dataServiceMock.response = 'error'; // invalid response or HTTP error
        const res = await service.get();
        expect(res).toBe(undefined);
    });

    it('get, second call', async () => {
        const res1 = await service.get();
        expect(dataServiceMock.get).toHaveBeenCalledTimes(1);
        const res2 = await service.get();
        expect(res2).not.toBe(undefined);
        expect(res2).toEqual(res1);
        expect(dataServiceMock.get).toHaveBeenCalledTimes(1); // still only one call
    });
});
