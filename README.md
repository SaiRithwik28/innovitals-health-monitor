# InnoVitals – IoT-Based Smart Health Monitoring and Emergency Response System

## Overview

InnoVitals is an advanced IoT-enabled health monitoring system designed for real-time patient monitoring and emergency response. The system integrates multiple biosensors with an ESP32 microcontroller to continuously track critical physiological parameters such as Blood Oxygen Saturation (SpO₂), Heart Rate, and Body Temperature.

To enhance patient safety, InnoVitals incorporates fall detection using the MPU-6050 Accelerometer and live location tracking through the NEO-6M GPS module. Health data and emergency alerts are transmitted wirelessly using the Telegram Bot API, enabling caregivers and healthcare professionals to access real-time patient information remotely.

## Key Features

* Real-time monitoring of SpO₂, Heart Rate, and Body Temperature
* Fall detection using MPU-6050 Accelerometer
* Live GPS location tracking with NEO-6M GPS module
* Instant emergency alerts through Telegram Bot
* Hardware SOS button for rapid assistance requests
* Wireless transmission of health data and location information
* Remote patient monitoring for caregivers and medical personnel
* Cost-effective and scalable healthcare solution

## System Architecture

1. Sensors collect patient health parameters.
2. ESP32 processes and analyzes sensor data.
3. MPU-6050 detects sudden falls or abnormal movement.
4. GPS module retrieves real-time location coordinates.
5. Telegram Bot API sends health updates and emergency notifications.
6. Caregivers receive alerts and can respond immediately.

## Hardware Components

* ESP32 Microcontroller
* MAX30102 SpO₂ and Heart Rate Sensor
* Temperature Sensor
* MPU-6050 Accelerometer and Gyroscope
* NEO-6M GPS Module
* SOS Push Button
* Power Supply Module

## Software and Technologies

* Embedded C / Arduino IDE
* ESP32 Development Framework
* Telegram Bot API
* IoT Communication Protocols
* GPS Location Services

## Applications

* Elderly Care Monitoring
* Remote Patient Monitoring
* Chronic Disease Management
* Home Healthcare Systems
* Emergency Medical Assistance

## Project Outcome

The system successfully provides continuous health monitoring, fall detection, and emergency communication through a low-cost IoT platform. By integrating real-time vital tracking with location-based emergency alerts, InnoVitals improves patient safety and enables faster medical intervention.

## Future Enhancements

* Cloud-based health data storage
* AI-powered health anomaly prediction
* Mobile application integration
* Medical report generation and analytics dashboard
* Multi-patient monitoring support
