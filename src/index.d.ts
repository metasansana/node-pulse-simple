import * as Buffer from 'buffer';

export class Connection {

    constructor(name: string);

    write(data: Buffer): void;

    close(): void;

}

