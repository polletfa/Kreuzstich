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
    }
}
