/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { Component, signal, OnInit } from '@angular/core';
import { RouterOutlet } from '@angular/router';

import { CoreService } from '@services/core-service/core-service';

@Component({
    selector: 'app-root',
    imports: [RouterOutlet],
    templateUrl: './main-component.html',
    styleUrl: './main-component.scss'
})
export class MainComponent implements OnInit {
    private core?: Core;
    protected readonly title = signal('gui-web');

    constructor(private coreService: CoreService) {}

    public async ngOnInit() {
        this.core = await this.coreService.get();

        const rgba: ColorSpace.ColorRGBA = {red: 59, green: 130, blue: 246, alpha: 204};
        const bg: ColorSpace.ColorRGBA = {red: 1, green: 2, blue: 3, alpha: 255};
        console.log("test", this.core.ColorSpace.compositeRGBAOntoBackground(rgba, bg));
        console.log("distance", this.core.ColorSpace.distance({lightness: 64, a: 12, b: -48}, {lightness: 79, a: 95, b: 10}, "CIE1976"));
    }
}
