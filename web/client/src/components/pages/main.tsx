'use client';

import { Card, CardDescription } from '../ui/card';

import { CaretSortIcon, ReloadIcon } from '@radix-ui/react-icons';
import {
    ColumnDef,
    ColumnFiltersState,
    SortingState,
    VisibilityState,
    flexRender,
    getCoreRowModel,
    getFilteredRowModel,
    getPaginationRowModel,
    getSortedRowModel,
    useReactTable,
} from '@tanstack/react-table';

import { Button } from '@/components/ui/button';
import {
    Table,
    TableBody,
    TableCell,
    TableHead,
    TableHeader,
    TableRow,
} from '@/components/ui/table';
import { useCallback, useEffect, useState } from 'react';
import { cn } from '@/lib/utils';
import {
    SensorSchema,
    SensorsSchema,
    SensorsType,
    SensorType,
} from '@/lib/zod.schema';

const TABLE_HEADER_CLASS = 'w-full flex px-0 justify-between md:text-xl';
const TABLE_CELL_CLASS = 'text-left px-1 font-medium text-lg';

const INTERVAL_TIME = 800;

export const columns: ColumnDef<SensorType>[] = [
    {
        accessorKey: 'id',
        header: ({ column }) => {
            return (
                <Button
                    className={TABLE_HEADER_CLASS}
                    variant="ghost"
                    onClick={() =>
                        column.toggleSorting(column.getIsSorted() === 'asc')
                    }
                >
                    id
                    <CaretSortIcon className="ml-2 h-4 w-4" />
                </Button>
            );
        },
        cell: ({ row }) => (
            <div className={TABLE_CELL_CLASS}>{row.getValue('id')}</div>
        ),
    },
    {
        accessorKey: 'temperature',
        header: ({ column }) => {
            return (
                <Button
                    className={TABLE_HEADER_CLASS}
                    variant="ghost"
                    onClick={() =>
                        column.toggleSorting(column.getIsSorted() === 'asc')
                    }
                >
                    nhiệt độ
                    <CaretSortIcon className="ml-2 h-4 w-4" />
                </Button>
            );
        },
        cell: ({ row }) => (
            <div className={TABLE_CELL_CLASS}>
                {row.getValue('temperature')}
            </div>
        ),
    },
    {
        accessorKey: 'humidity',
        header: ({ column }) => {
            return (
                <Button
                    className={TABLE_HEADER_CLASS}
                    variant="ghost"
                    onClick={() =>
                        column.toggleSorting(column.getIsSorted() === 'asc')
                    }
                >
                    độ ẩm
                    <CaretSortIcon className="ml-2 h-4 w-4" />
                </Button>
            );
        },
        cell: ({ row }) => (
            <div className={TABLE_CELL_CLASS}>{row.getValue('humidity')}</div>
        ),
    },
    {
        accessorKey: 'soilMoisture',
        header: ({ column }) => {
            return (
                <Button
                    className={TABLE_HEADER_CLASS}
                    variant="ghost"
                    onClick={() =>
                        column.toggleSorting(column.getIsSorted() === 'asc')
                    }
                >
                    độ ẩm đất
                    <CaretSortIcon className="ml-2 h-4 w-4" />
                </Button>
            );
        },
        cell: ({ row }) => (
            <div className={TABLE_CELL_CLASS}>
                {row.getValue('soilMoisture')}
            </div>
        ),
    },
    {
        accessorKey: 'createdAt',
        header: ({ column }) => {
            return (
                <Button
                    className={TABLE_HEADER_CLASS}
                    variant="ghost"
                    onClick={() =>
                        column.toggleSorting(column.getIsSorted() === 'asc')
                    }
                >
                    thời gian
                    <CaretSortIcon className="ml-2 h-4 w-4" />
                </Button>
            );
        },
        cell: ({ row }) => (
            <div className={TABLE_CELL_CLASS}>
                {`${(row.getValue('createdAt') as Date).toLocaleTimeString(
                    'vn'
                )} ${(row.getValue('createdAt') as Date).toLocaleDateString(
                    'vn'
                )}`}
            </div>
        ),
    },
];

const Main = () => {
    const [rows, setRows] = useState<SensorsType>([]);
    const [latest, setLatest] = useState<SensorType | undefined>(undefined);

    const [sorting, setSorting] = useState<SortingState>([]);

    const table = useReactTable({
        data: rows,
        columns,
        onSortingChange: setSorting,
        getCoreRowModel: getCoreRowModel(),
        getSortedRowModel: getSortedRowModel(),
        getFilteredRowModel: getFilteredRowModel(),
        state: {
            sorting,
        },

    });

    const handleFetchData = useCallback(async () => {
        const res = await fetch('http://localhost:8080/api/v1/sensors');

        if (!res) return;

        const parse = SensorsSchema.safeParse(await res.json());
        if (parse.success) {
            console.log(parse.data)
            setRows(parse.data);
        }
    }, []);

    const handleFetchLatest = useCallback(async () => {
        const res = await fetch('http://localhost:8080/api/v1/sensors/lastest');

        if (!res) return;

        const parse = SensorSchema.safeParse(await res.json());
        if (parse.success) {
            setLatest(parse.data);
        }
    }, []);

    useEffect(() => {
        handleFetchData();
        handleFetchLatest();

        const id = setInterval(handleFetchLatest, INTERVAL_TIME);

        return () => {
            clearInterval(id);
        };
    }, [handleFetchData, handleFetchLatest]);

    return (
        <main className="flex flex-col md:px-2">
            <div className="flex flex-col w-full">
                <div className="grid grid-rows-3 md:grid-rows-1 md:grid-cols-3 gap-3">
                    <div className="px-2 md:mb-2">
                        <CardDescription className="md:text-xl">
                            ĐỘ ẨM KHÔNG KHÍ
                        </CardDescription>
                        <div className=" text-6xl sm:text-7xl text-right">
                            {latest?.humidity}%
                        </div>
                        <div className="flex justify-end bg-gray-200 h-3 md:h-5 w-full rounded-full">
                            <div
                                className="h-full bg-gray-800 rounded-full"
                                style={{
                                    width: `${latest?.humidity || 0}%`,
                                }}
                            ></div>
                        </div>
                    </div>
                    <div className="px-2 md:mb-2">
                        <CardDescription className="md:text-xl">
                            ĐỘ ẨM ĐẤT
                        </CardDescription>
                        <div className="text-6xl sm:text-7xl text-right">
                            {latest?.soilMoisture}%
                        </div>
                        <div className="flex justify-end bg-gray-200 h-3 md:h-5 w-full rounded-full">
                            <div
                                className="h-full bg-gray-800 rounded-full"
                                style={{
                                    width: `${latest?.soilMoisture || 0}%`,
                                }}
                            ></div>
                        </div>
                    </div>
                    <div className="px-2">
                        <CardDescription className="md:text-xl">
                            NHIỆT ĐỘ
                        </CardDescription>
                        <div
                            className={cn(
                                'flex flex-grow justify-end items-end text-6xl sm:text-7xl',
                                latest?.temperature && {
                                    'text-blue-500': latest.temperature > -200,
                                    'text-green-500': latest.temperature > 22,
                                    'text-yellow-500': latest.temperature > 27,
                                    'text-red-500': latest.temperature > 35,
                                }
                            )}
                        >
                            {latest?.temperature}
                            <div className="ml-1">&deg;C</div>
                        </div>
                    </div>
                </div>
            </div>

            <div className="w-full p-2 md:pt-3">
                <div className="flex justify-end">
                    <Button variant="outline" onClick={handleFetchData}>
                        <ReloadIcon className="mr-1" />
                        Refresh
                    </Button>
                </div>
                <div className="rounded-md w-full">
                    <Table>
                        <TableHeader>
                            {table.getHeaderGroups().map((headerGroup) => (
                                <TableRow key={headerGroup.id}>
                                    {headerGroup.headers.map((header) => {
                                        return (
                                            <TableHead key={header.id}>
                                                {header.isPlaceholder
                                                    ? null
                                                    : flexRender(
                                                          header.column
                                                              .columnDef.header,
                                                          header.getContext()
                                                      )}
                                            </TableHead>
                                        );
                                    })}
                                </TableRow>
                            ))}
                        </TableHeader>
                        <TableBody className="">
                            {table.getRowModel().rows?.length ? (
                                table.getRowModel().rows.map((row, ind) => (
                                    <TableRow
                                        className={cn('border-none', {
                                            'bg-gray-50': ind % 2,
                                        })}
                                        key={row.id}
                                    >
                                        {row.getVisibleCells().map((cell) => (
                                            <TableCell key={cell.id}>
                                                {flexRender(
                                                    cell.column.columnDef.cell,
                                                    cell.getContext()
                                                )}
                                            </TableCell>
                                        ))}
                                    </TableRow>
                                ))
                            ) : (
                                <TableRow>
                                    <TableCell
                                        colSpan={columns.length}
                                        className="h-24 text-center"
                                    >
                                        No results.
                                    </TableCell>
                                </TableRow>
                            )}
                        </TableBody>
                    </Table>
                </div>
            </div>
        </main>
    );
};

export default Main;
