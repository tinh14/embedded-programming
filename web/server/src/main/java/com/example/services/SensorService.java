package com.example.services;

import com.example.entities.SensorDataEntity;

import java.util.List;

public interface SensorService {
    List<SensorDataEntity> findAll();
    SensorDataEntity findLastest();
    SensorDataEntity create(SensorDataEntity sensorData) throws Exception;
}
