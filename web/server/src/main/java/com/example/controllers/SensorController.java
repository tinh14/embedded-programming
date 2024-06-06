package com.example.controllers;

import com.example.entities.SensorDataEntity;
import com.example.services.SensorService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/v1/sensors")
public class SensorController {

    @Autowired
    private SensorService sensorService;

    @GetMapping
    public ResponseEntity<List<SensorDataEntity>> getAllSensorData() {
        List<SensorDataEntity> sensors = sensorService.findAll();
        return ResponseEntity.ok(sensors);
    }

    @GetMapping("/lastest")
    public ResponseEntity<SensorDataEntity> getLatestSensorData() {
        SensorDataEntity sensor = sensorService.findLastest();
        return ResponseEntity.ok(sensor);
    }

    @PostMapping
    public ResponseEntity<String> create(@RequestBody SensorDataEntity sensorData) {
        try {
            System.out.println(sensorData.toString());
            sensorService.create(sensorData);
            return ResponseEntity.ok("Sensor data created successfully!");
        } catch (Exception e) {
            return ResponseEntity.badRequest().body(e.getMessage());
        }
    }
}
