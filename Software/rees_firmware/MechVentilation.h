/** Mechanical ventilation.
 *
 * @file MechVentilation.h
 *
 * This is the mechanical ventilation software module.
 * It handles the mechanical ventilation control loop.
 */
#ifndef INC_MECHANICAL_VENTILATION_H
#define INC_MECHANICAL_VENTILATION_H

#include <inttypes.h>
#include "PID.h"

/** States of the mechanical ventilation. */
enum State {
    State_Init = 0,               /**< Initializing. */
    State_Idle = 1,               /**< Idle. */
    State_WaitTrigger = 2,        /**< Wait for trigger. */
    State_StartInsufflation = 3,  /**< Start insufflation. */
    State_Insufflation = 4,       /**< Insufflating (PID control). */
    State_StopInsufflation = 5,   /**< Stop insufflation. */
    State_WaitExsufflation = 6,   /**< Wait for the patient to exsufflate. */
    State_Shutdown = 7            /**< Shutdown. */
};

/**
 * This is the mechanical ventilation class.
 */
class MechVentilation {
public:
	/**
	 * Constructor (no trigger).
	 *
     * @param[in]   mlTidalVolume             Tidal volume in millilitres.
	 * @param[in]   secTimeoutInsufflation    Insufflation timeout in seconds.
	 * @param[in]   secTimeoutExsufflation    Exsufflation timeout in seconds.
     * @param[in]   speedInsufflation         Insufflation speed. @todo Denote units.
     * @param[in]   speedExsufflation         Exsufflation speed. @todo Denote units.
     *
	 */
	MechVentilation(
        float mlTidalVolume,
        float secTimeoutInsufflation,
        float secTimeoutExsufflation,
        float speedInsufflation,
        float speedExsufflation
    );

    /**
	 * Constructor (triggered mechanical ventilation).
	 *
     * @param[in]   mlTidalVolume             Tidal volume in millilitres.
	 * @param[in]   secTimeoutInsufflation    Insufflation timeout in seconds.
	 * @param[in]   secTimeoutExsufflation    Exsufflation timeout in seconds.
     * @param[in]   speedInsufflation         Insufflation speed. @todo Denote units.
     * @param[in]   speedExsufflation         Exsufflation speed. @todo Denote units.
     * @param[in]   lpmFluxTriggerValue       Flux trigger value in Litres Per Minute.
     *
	 */
	MechVentilation(
        float mlTidalVolume,
        float secTimeoutInsufflation,
        float secTimeoutExsufflation,
        float speedInsufflation,
        float speedExsufflation,
        float lpmFluxTriggerValue
    );

    /* Setters/getters */
    /* Set tidal volume */
    void setTidalVolume(float mlTidalVolume);
    /** Set insufflation timeout. */
    void setTimeoutInsufflation(float secTimeoutInsufflation);
    /** Set exsufflation timeout. */
    void setTimeoutExsufflation(float secTimeoutExsufflation);
    /** Set insufflation speed. */
    void setSpeedInsufflation(float speedInsufflation);
    /** Set exsufflation speed. */
    void setSpeedExsufflation(float speedExsufflation);

    /** Start mechanical ventilation. */
    void start(void);
    /** Stop mechanical ventilation. */
    void stop(void);
    /** Update mechanical ventilation.
     *
     * If any control variable were to change, new value
     * would be applied at the beginning of the next ventilation
     * cycle.
     *
     * @note This method must be called on the main loop.
     */
    void update(void);

private:
    /** Generic initialization. */
    void _init(
        float mlTidalVolume,
        float secTimeoutInsufflation,
        float secTimeoutExsufflation,
        float speedInsufflation,
        float speedExsufflation,
        float lpmFluxTriggerValue
    );

    /** Set state. */
    void _setState(State state);

    /* Configuration parameters */
    /** Tidal volume in millilitres. */
    float _cfgmlTidalVolume;
    /** Flux trigger value in litres per minute. */
    float _cfgLpmFluxTriggerValue;
    /**  Insufflation timeout in seconds. */
    float _cfgSecTimeoutInsufflation;
    /* Exsufflation timeout in seconds. */
    float _cfgSecTimeoutExsufflation;
    /** Insufflation speed. @todo Denote units. */
    float _cfgSpeedInsufflation;
    /** Exsufflation speed. @todo Denote units. */
    float _cfgSpeedExsufflation;

    /* Internal state */
    /** Previous state. @todo Consider removing. */
    State _previousState;
    /** Current state. */
    State _currentState;
    /** Next state. @todo Consider removing. */
    State _nextState;
    /** Timer counter in seconds. */
    uint8_t _secTimerCnt;
    /**  Insufflation timeout in seconds. */
    float _secTimeoutInsufflation;
    /** Exsufflation timeout in seconds. */
    float _secTimeoutExsufflation;
    /** Insufflation speed. @todo Denote units. */
    float _speedInsufflation;
    /** Exsufflation speed. @todo Denote units. */
    float _speedExsufflation;

    /* @todo PID stuff */

};

#endif /* INC_MECHANICAL_VENTILATION_H */
