/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { Component, OnInit, signal } from '@angular/core';

import type * as Core from '@wrapper-wasm';
import { Version } from '@version';

import { CoreService } from '@services/core-service/core-service';
import { DataService } from '@services/data-service/data-service';
import { ThreadListService } from '@services/thread-list-service/thread-list-service';

@Component({
    selector: 'app-designer-component',
    imports: [],
    templateUrl: './designer-component.html',
    styleUrl: './designer-component.scss',
})
export class DesignerComponent implements OnInit {
    private core?: Core.Module;

    private coreVersion: string = '';
    private dataVersion: string = '';
    private guiVersion: string = Version.getVersionString();

    public testsOutput = signal<{level: 'error'|'info', message: string}[]>([]);

    constructor(
        private coreService: CoreService,
        private dataService: DataService,
        private threadListsService: ThreadListService
    ) {}

    public async ngOnInit() {
        await Promise.all([
            this.coreService.get().then(core => {
                this.core = core;
                this.coreVersion = core.Version.getVersionString();
            }).catch(error => {
                this.error(error);
            }),
            this.dataService.getVersion().then(version => {
                this.dataVersion = version.VERSION_STRING;
            }).catch(error => {
                this.error(error);
            })
        ]);

        if(this.core) {
            this.log('Versions:');
            this.log('- Core: ' + this.coreVersion);
            this.log('- Data: ' + this.dataVersion);
            this.log('- Gui: ' + this.guiVersion);
            if(this.coreVersion !== this.guiVersion || this.dataVersion !== this.guiVersion) {
                this.error('Version mismatch!');
            }

            // tests
            const start = Date.now();
            const rgba: Core.ColorSpace.ColorRGBA = {red: 59, green: 130, blue: 246, alpha: 204};
            const bg: Core.ColorSpace.ColorRGBA = {red: 1, green: 2, blue: 3, alpha: 255};
            this.log("test", this.core.ColorSpace.compositeRGBAOntoBackground(rgba, bg));
            this.log("distance", this.core.ColorSpace.distance({lightness: 64, a: 12, b: -48}, {lightness: 79, a: 95, b: 10}, "CIE1976"));

            const lists = await this.threadListsService.get();
            const dmc = lists?.find(i => i.name() === 'DMC');

            if(dmc) {
                this.log(dmc.get("HSL", "ASC").map(t => t.name()));
                this.log(dmc.get("HSL", "DESC").map(t => t.name()));
                this.log(`closest to a00000: ${dmc.findClosest({red: 0xa0, green: 0, blue: 0, alpha: 255}, "CIEDE2000")?.name()}`);
            }

            this.log((Date.now() - start) + " ms");
        }
    }

    private error(...data: any[]){
        this.writeMessage('error', data);
    }

    private log(...data: any[]){
        this.writeMessage('info', data);
    }

    private writeMessage(level: 'error'|'info', data: any[]) {
        const outputs = this.testsOutput();
        for(const str of data.map(d => typeof d === 'string' ? d : JSON.stringify(d))) {
            outputs.push({level, message: str});
        }
        this.testsOutput.set([...outputs]);
    }
}
