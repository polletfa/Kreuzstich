import { Injectable, signal, computed } from '@angular/core';

import { DataService } from '@services/data-service/data-service';

import * as api from '@api/User';

/**
 * Service for login and user management
 */
@Injectable({
    providedIn: 'root',
})
export class UserService {
    private _user = signal<api.GetUserStatusResponse|null|undefined>(undefined); // undefined: not yet initialized, null: not logged in
    readonly user = this._user.asReadonly();
    readonly isReady = computed(() => this._user() !== undefined);

    constructor(private dataService: DataService) {
        this.dataService.get<api.GetUserStatusResponse>('user/status', api.GetUserStatusResponseSchema)
            .then((user) => { this._user.set(user); })
            .catch(() => { this._user.set(null)});
    }

    public async login(request: api.PostUserLoginRequest): Promise<boolean> {
        try {
            const user = await this.dataService.post<api.PostUserLoginRequest, api.PostUserLoginResponse>('user/login', request, api.PostUserLoginResponseSchema);
            if(!user) {
                console.error('Login failed.');
                return false;
            }
            this._user.set(user);
            return true;
        } catch(error) {
            console.error(error);
            return false;
        }
    }

    public async logout(): Promise<void> {
        try {
            const res = await this.dataService.get<api.GetUserLogoutResponse>('user/logout', api.GetUserLogoutResponseSchema);
            if(res.success) {
                console.log('Logged out.');
                this._user.set(null);
            }
        } catch(error) {
            console.error(error);
        }
    }
}
