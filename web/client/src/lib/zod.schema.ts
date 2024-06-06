import { z } from 'zod';

export const SensorSchema = z.object({
    id: z.number(),
    temperature: z.number(),
    humidity: z.number(),
    soilMoisture: z.number(),
    createdAt: z.coerce.date(),
});

export type SensorType = z.infer<typeof SensorSchema>;

export const SensorsSchema = z.array(SensorSchema);

export type SensorsType = z.infer<typeof SensorsSchema>;
