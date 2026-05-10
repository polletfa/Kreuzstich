/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { Component, effect, OnInit } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { MatProgressSpinnerModule } from '@angular/material/progress-spinner';
import { MatButtonModule } from '@angular/material/button';
import { MatCheckboxModule } from '@angular/material/checkbox';
import { FormsModule } from '@angular/forms';

import type * as Core from '@wrapper-wasm';
import { Version } from '@version';

import { CoreService } from '@services/core-service/core-service';
import { DataService } from '@services/data-service/data-service';
import { UserService } from '@services/user-service/user-service';

@Component({
    selector: 'app-root',
    imports: [
        RouterOutlet,
        MatProgressSpinnerModule,
        MatButtonModule,
        MatCheckboxModule,
        FormsModule
    ],
    templateUrl: './main-component.html',
    styleUrl: './main-component.scss'
})
export class MainComponent implements OnInit {
    private core?: Core.Module;

    private coreVersion: string = '';
    private dataVersion: string = '';
    private guiVersion: string = Version.getVersionString();

    public persistentLogin = true;

    constructor(
        private coreService: CoreService,
        private dataService: DataService,
        public userService: UserService
    ) {
        effect(() => {
            console.log('User changed: ', this.userService.user());
        });
    }

    public async ngOnInit() {
        this.core = await this.coreService.get();

        await Promise.all([
            this.coreService.get()
                .then(core => {
                    this.core = core;
                    this.coreVersion = core.Version.getVersionString();
                })
                .catch(error => {
                    console.error(error);
                }),
            this.dataService.getVersion()
                .then(version => {
                    this.dataVersion = version.VERSION_STRING;
                })
                .catch(error => {
                    console.error(error);
                })
        ]);

        console.log('Versions:');
        console.log('- Core: ' + this.coreVersion);
        console.log('- Data: ' + this.dataVersion);
        console.log('- Gui: ' + this.guiVersion);
        if(this.coreVersion !== this.guiVersion || this.dataVersion !== this.guiVersion) {
            console.error('Version mismatch!');
        }

        // tests
        const start = Date.now();
        const rgba: Core.ColorSpace.ColorRGBA = {red: 59, green: 130, blue: 246, alpha: 204};
        const bg: Core.ColorSpace.ColorRGBA = {red: 1, green: 2, blue: 3, alpha: 255};
        console.log("test", this.core.ColorSpace.compositeRGBAOntoBackground(rgba, bg));
        console.log("distance", this.core.ColorSpace.distance({lightness: 64, a: 12, b: -48}, {lightness: 79, a: 95, b: 10}, "CIE1976"));

        const threads = [
            new this.core.Thread("black", "000000"),
            new this.core.Thread("white", "ffffff"),
            new this.core.Thread("red", "ff0000"),
            new this.core.Thread("green", "00ff00"),
            new this.core.Thread("blue", "0000ff")
        ];


        try {
            using list = new this.core.ThreadList(threads);
            console.log(list.get("HSL", "ASC").map(t => t.name()));
            console.log(list.get("HSL", "DESC").map(t => t.name()));
            console.log(`closest to a00000: ${list.findClosest({red: 0xa0, green: 0, blue: 0, alpha: 255}, "CIEDE2000")?.name()}`);
        } finally {
            threads.forEach(t => t.delete());
        }

        console.log((Date.now() - start) + " ms");

        console.log(this.userService.user());
    }

    public onTest() {
        if(this.userService.user()) {
            this.userService.logout();
        } else {
            this.userService.login({email: 'polletfa@posteo.de', password: 'test', persist: this.persistentLogin});
        }
    }
}
