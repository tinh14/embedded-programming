package com.example.repositories;

import com.example.entities.SensorDataEntity;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;

public interface SensorRepository extends JpaRepository<SensorDataEntity, Long> {
    Optional<SensorDataEntity> findFirstByOrderByIdDesc();
}
