/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import fs from 'fs/promises';

export default async function loadSqlFile(filepath: string, importAttributes: {[key: string]: string}): string {
    let sql = await fs.readFile(filepath, 'utf-8');

    // Strip single-line comments
    sql = sql.replace(/--.*$/gm, '');
    // Strip multi-line comments
    sql = sql.replace(/\/\*[\s\S]*?\*\//g, '');
    // Collapse excess whitespace
    sql = sql.replace(/\s+/g, ' ').trim();

    // check conditional flags
    let match: RegExpMatchArray|null = null;
    do {
        match = sql.match(/^(.*?)@with\s*\((.*?)\)\s*{(.*?)}(.*)$/);
        if(match && match.length >= 5) {
            if(importAttributes[match[2]] === 'true') {
                sql = `${match[1]} ${match[3]} ${match[4]}`;
            } else {
                sql = `${match[1]} ${match[4]}`;
            }
        }
    } while(match);

    // Collapse excess whitespace again
    sql = sql.replace(/\s+/g, ' ').trim();

    return `export default ${JSON.stringify(sql)}`;
}
