/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

type StringProperty = {type: 'string', required: boolean, default?: string, value?: string};
type NumberProperty = {type: 'number', required: boolean, default?: number, value?: number};

export class ConfigService {
    private properties: {[key: string]: StringProperty|NumberProperty} = {
        LOGDIR:      {type: 'string', required: false                },
        PORT:        {type: 'number', required: true                 },
        DB_HOST:     {type: 'string', required: true                 },
        DB_PORT:     {type: 'number', required: false, default: 5432 },
        DB_DB:       {type: 'string', required: true                 },
        DB_USER:     {type: 'string', required: true                 },
        DB_PASSWORD: {type: 'string', required: true                 },
        JWT_SECRET:  {type: 'string', required: true                 }
    };
    private readonly prefix = 'KREUZSTICH_DATA_WEB_';

    constructor() {
        // validate

        for(const prop in this.properties) {
            if(!this.properties[prop]) {
                continue;
            }
            const value = process.env[this.prefix + prop] == '' ? undefined : process.env[this.prefix + prop];
            if(this.properties[prop].required && !value) {
                throw new Error(`Missing environment variable ${this.prefix}${prop}`);
            } else if(value && this.properties[prop].type === 'number') {
                const asNum = Number(value);
                if(Number.isNaN(asNum)) {
                    throw new Error(`Invalid value for environment variable ${this.prefix}${prop} (not a number): ${value}`);
                }
            }
            this.properties[prop].value = value && value !== '' ? value : this.properties[prop].default;
        }
    }

    public get logDir(): string|undefined {
        return (this.properties['LOGDIR'] as StringProperty).value;
    }
    public get port(): number {
        return (this.properties['PORT'] as NumberProperty).value as number;
    }
    public get dbHost(): string {
        return (this.properties['DB_HOST'] as StringProperty).value as string;
    }
    public get dbPort(): number {
        return (this.properties['DB_PORT'] as NumberProperty).value as number;
    }
    public get dbDatabase(): string {
        return (this.properties['DB_DB'] as StringProperty).value as string;
    }
    public get dbUser(): string {
        return (this.properties['DB_USER'] as StringProperty).value as string;
    }
    public get dbPassword(): string {
        return (this.properties['DB_PASSWORD'] as StringProperty).value as string;
    }
    public get jwtSecret(): string {
        return (this.properties['JWT_SECRET'] as StringProperty).value as string;
    }
}
