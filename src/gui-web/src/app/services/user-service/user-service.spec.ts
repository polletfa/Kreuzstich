import { TestBed } from '@angular/core/testing';

import { DataService } from '@services/data-service/data-service';
import { UserService } from './user-service';

class DataServiceMock {
    constructor(public response: boolean|'error', public user: string) {}

    private async mockResponse() {
        switch(this.response) {
            case true:
                return {success: true, data: {id: 1, email: this.user, name: 'Test User'}};
            case false:
                return {success: false, error: 'Unauthorized'};
            case 'error':
                throw new Error('invalid response');
        }
    }

    get = vi.fn().mockImplementation(async () => {
        return this.mockResponse();
    });
    post = vi.fn().mockImplementation(async () => {
        return this.mockResponse();
    });
}

async function testLogin(dataServiceMock: DataServiceMock, service: UserService, response: boolean|'error') {
    const currentUser = JSON.parse(JSON.stringify(service.user()));

    dataServiceMock.response = response;
    dataServiceMock.user = 'test';

    const res = await service.login({email: "test", password: "test", persist: true});
    expect(res).toBe(response == true ? true : false);

    if(response === true) {
        // User has been set
        expect(service.user()).toEqual({id: 1, email: 'test', name: 'Test User'});
    } else {
        // User has not been changed
        expect(service.user()).toEqual(currentUser);
    }
}

async function testLogout(dataServiceMock: DataServiceMock, service: UserService, response: boolean|'error') {
    const currentUser = JSON.parse(JSON.stringify(service.user()));

    dataServiceMock.response = response;

    const res = await service.logout();
    expect(res).toBe(response == true ? true : false);

    if(response === true) {
        // User has been unset
        expect(service.user()).toEqual(null);
    } else {
        // User has not been changed
        expect(service.user()).toEqual(currentUser);
    }
}

describe('UserService, not logged in', () => {
    let service: UserService;
    let dataServiceMock: DataServiceMock;

    beforeEach(() => {
        dataServiceMock = new DataServiceMock(false, 'init');

        TestBed.configureTestingModule({
            providers: [
                {provide: DataService, useValue: dataServiceMock}
            ]
        });
        service = TestBed.inject(UserService);
    });

    it('should be created', () => {
        expect(service).toBeTruthy();
    });

    it('user status', async () => {
        // wait for a moment, to give the service time to initialize
        await new Promise(r => setTimeout(r, 1000));
        expect(service.isReady()).toBe(true);
        expect(service.user()).toBe(null);
    });

    it('login, success', async () => { await testLogin(dataServiceMock, service, true); });
    it('login, failure', async () => { await testLogin(dataServiceMock, service, false); });
    it('login, error', async () => { await testLogin(dataServiceMock, service, 'error'); });

    it('logout, success', async () => { await testLogout(dataServiceMock, service, true); });
    it('logout, failure', async () => { await testLogout(dataServiceMock, service, false); });
    it('logout, error', async () => { await testLogout(dataServiceMock, service, 'error'); });
});

describe('UserService, logged in', () => {
    let service: UserService;
    let dataServiceMock: DataServiceMock;

    beforeEach(() => {
        dataServiceMock = new DataServiceMock(true, 'init');

        TestBed.configureTestingModule({
            providers: [
                {provide: DataService, useValue: dataServiceMock}
            ]
        });
        service = TestBed.inject(UserService);
    });

    it('should be created', () => {
        expect(service).toBeTruthy();
    });

    it('user status', async () => {
        // wait for a moment, to give the service time to initialize
        await new Promise(r => setTimeout(r, 1000));
        expect(service.isReady()).toBe(true);
        expect(service.user()).toEqual({id: 1, email: 'init', name: 'Test User'});
    });

    it('login, success', async () => { await testLogin(dataServiceMock, service, true); });
    it('login, failure', async () => { await testLogin(dataServiceMock, service, false); });
    it('login, error', async () => { await testLogin(dataServiceMock, service, 'error'); });

    it('logout, success', async () => { await testLogout(dataServiceMock, service, true); });
    it('logout, failure', async () => { await testLogout(dataServiceMock, service, false); });
    it('logout, error', async () => { await testLogout(dataServiceMock, service, 'error'); });
});
