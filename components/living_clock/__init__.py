import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output
from esphome.const import CONF_ID, CONF_HUMIDITY, CONF_TEMPERATURE, CONF_TIME 

living_clock_ns = cg.esphome_ns.namespace('living_clock')
LivingClockHub = living_clock_ns.class_('LivingClockHub', cg.Component)
Clock = tplink_ns.struct('Clock')

DEPENDENCIES = ['json']
AUTO_LOAD = ['json']

CONF_CLOCKS = 'clocks'
CONF_OUT_TEMP = 'out_temp'
CONF_IN_TEMP = 'in_temp'
CONF_IN_HUM = 'in_huminity'

CLOCK_SCHEMA = cv.Schema({
    cv.Required(CONF_OUT_TEMP): cv.use_id(output.FloatOutput),
    cv.Required(CONF_IN_TEMP): cv.use_id(output.FloatOutput),
    cv.Required(CONF_IN_HUM): cv.use_id(output.FloatOutput),
})

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(LivingClockHub),
    cv.Optional(CONF_CLOCKS): cv.ensure_list(CLOCK_SCHEMA),
})

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)

    for conf in config.get(CONF_CLOCKS, []):
        out_temp = 0
        if CONF_OUT_TEMP in conf:
            out_temp = yield cg.get_variable(conf[CONF_OUT_TEMP])
        in_temp = 0
        if CONF_IN_TEMP in conf:
            in_temp = yield cg.get_variable(conf[CONF_IN_TEMP])
        in_huminity = 0
        if CONF_IN_HUM in conf:
            in_huminity = yield cg.get_variable(conf[CONF_IN_HUM])
        
        clock = cg.StructInitializer(
            Clock,
            ('out_temp', out_temp),
            ('in_temp', in_temp),
            ('in_huminity', in_huminity)
        )

        cg.add(var.add_clock(Clock))