import { Injectable, signal, computed } from '@angular/core';

import { DataService } from '@services/data-service/data-service';

import * as api from '@datatypes/api/User';

/**
 * Service for login and user management
 */
@Injectable({
    providedIn: 'root',
})
export class UserService {
    private _user = signal<api.User|null|undefined>(undefined); // undefined: not yet initialized, null: not logged in
    readonly user = this._user.asReadonly();
    readonly isReady = computed(() => this._user() !== undefined);

    constructor(private dataService: DataService) {
        this.dataService.get<api.GetUserStatusResponse>('user/status', api.GetUserStatusResponseSchema).then((user) => {
            if(user.success && user.data) {
                this._user.set(user.data);
            } else {
                this._user.set(null);
            }
        }).catch(() => { this._user.set(null)});
    }

    public async login(request: api.PostUserLoginRequest): Promise<boolean> {
        try {
            const user = await this.dataService.post<api.PostUserLoginRequest, api.PostUserLoginResponse>('user/login', request, api.PostUserLoginResponseSchema);
            if(!user.success || !user.data ) {
                console.error('Login failed.');
                return false;
            }
            this._user.set(user.data);
            return true;
        } catch(error) {
            console.error(error);
            return false;
        }
    }

    public async logout(): Promise<boolean> {
        try {
            const res = await this.dataService.get<api.GetUserLogoutResponse>('user/logout', api.GetUserLogoutResponseSchema);
            if(res.success) {
                console.log('Logged out.');
                this._user.set(null);
            }
            return res.success;
        } catch(error) {
            console.error(error);
            return false;
        }
    }
}
