package com.example.entities;

import lombok.Getter;
import lombok.Setter;
import org.hibernate.annotations.CreationTimestamp;

import javax.persistence.*;
import java.util.Date;

@Entity
@Setter
@Getter
public class SensorDataEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(nullable = false)
    private Integer temperature;

    @Column(nullable = false)
    private Integer humidity;

    @Column(nullable = false)
    private Integer soilMoisture;

    @Column(nullable = false, updatable = false)
    @CreationTimestamp
    private Date createdAt;

    @Override
    public String toString() {
        return "SensorDataEntity{" +
                "id=" + id +
                ", temperature=" + temperature +
                ", humidity=" + humidity +
                ", soilMoisture=" + soilMoisture +
                ", createdAt=" + createdAt +
                '}';
    }
}
