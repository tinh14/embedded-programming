import Main from '@/components/pages/main';
import { Metadata } from 'next/types';

export const metadata: Metadata = {
    title: 'SENSORS',
};

export default function Home() {
    return (
        <>
            <header className="h-16 flex items-center px-1 md:px-2 mb-1">
                <h1 className="text-3xl font-semibold ">SENSORS</h1>
            </header>
            <Main />
        </>
    );
}
