package com.example.services;

import com.example.entities.SensorDataEntity;
import com.example.repositories.SensorRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Sort;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;

@Service
@Transactional
public class SensorServiceImpl implements SensorService {

    private static final Logger logger = LoggerFactory.getLogger(SensorServiceImpl.class);

    @Autowired
    private SensorRepository sensorRepo;

    @Override
    @Transactional(readOnly = true)
    public List<SensorDataEntity> findAll() {
        return sensorRepo.findAll(Sort.by(Sort.Direction.DESC, "id"));
    }

    @Override
    @Transactional(readOnly = true)
    public SensorDataEntity findLastest() {
        Optional<SensorDataEntity> sensorDataWrapper = sensorRepo.findFirstByOrderByIdDesc();
        return sensorDataWrapper.orElse(null);
    }

    @Override
    public SensorDataEntity create(SensorDataEntity sensorData) throws Exception {
        try {
            return sensorRepo.save(sensorData);
        } catch (Exception e) {
            logger.error(e.getMessage());
            throw new Exception("Error creating the sensor data");
        }
    }
}
