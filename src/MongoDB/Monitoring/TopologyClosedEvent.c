/*
 * Copyright 2021-present MongoDB, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <php.h>
#include <Zend/zend_interfaces.h>

#include "php_phongo.h"
#include "phongo_error.h"

#include "BSON/ObjectId.h"

zend_class_entry* php_phongo_topologyclosedevent_ce;

/* {{{ proto MongoDB\BSON\ObjectId TopologyClosedEvent::getTopologyId()
   Returns this event's topology id */
static PHP_METHOD(TopologyClosedEvent, getTopologyId)
{
	php_phongo_topologyclosedevent_t* intern = Z_TOPOLOGYCLOSEDEVENT_OBJ_P(getThis());

	PHONGO_PARSE_PARAMETERS_NONE();

	phongo_objectid_init(return_value, &intern->topology_id);
} /* }}} */

/* {{{ MongoDB\Driver\Monitoring\TopologyClosedEvent function entries */
ZEND_BEGIN_ARG_INFO_EX(ai_TopologyClosedEvent_void, 0, 0, 0)
ZEND_END_ARG_INFO()

static zend_function_entry php_phongo_topologyclosedevent_me[] = {
	/* clang-format off */
	ZEND_NAMED_ME(__construct, PHP_FN(MongoDB_disabled___construct), ai_TopologyClosedEvent_void, ZEND_ACC_PRIVATE | ZEND_ACC_FINAL)
	PHP_ME(TopologyClosedEvent, getTopologyId, ai_TopologyClosedEvent_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	ZEND_NAMED_ME(__wakeup, PHP_FN(MongoDB_disabled___wakeup), ai_TopologyClosedEvent_void, ZEND_ACC_PUBLIC | ZEND_ACC_FINAL)
	PHP_FE_END
	/* clang-format on */
};
/* }}} */

/* {{{ MongoDB\Driver\Monitoring\TopologyClosedEvent object handlers */
static zend_object_handlers php_phongo_handler_topologyclosedevent;

static void php_phongo_topologyclosedevent_free_object(zend_object* object) /* {{{ */
{
	php_phongo_topologyclosedevent_t* intern = Z_OBJ_TOPOLOGYCLOSEDEVENT(object);

	zend_object_std_dtor(&intern->std);
} /* }}} */

static zend_object* php_phongo_topologyclosedevent_create_object(zend_class_entry* class_type) /* {{{ */
{
	php_phongo_topologyclosedevent_t* intern = zend_object_alloc(sizeof(php_phongo_topologyclosedevent_t), class_type);

	zend_object_std_init(&intern->std, class_type);
	object_properties_init(&intern->std, class_type);

	intern->std.handlers = &php_phongo_handler_topologyclosedevent;

	return &intern->std;
} /* }}} */

static HashTable* php_phongo_topologyclosedevent_get_debug_info(phongo_compat_object_handler_type* object, int* is_temp) /* {{{ */
{
	php_phongo_topologyclosedevent_t* intern;
	zval                              retval = ZVAL_STATIC_INIT;

	intern   = Z_OBJ_TOPOLOGYCLOSEDEVENT(PHONGO_COMPAT_GET_OBJ(object));
	*is_temp = 1;
	array_init_size(&retval, 1);

	{
		zval topology_id;
		phongo_objectid_init(&topology_id, &intern->topology_id);
		ADD_ASSOC_ZVAL_EX(&retval, "topologyId", &topology_id);
	}

	return Z_ARRVAL(retval);
} /* }}} */
/* }}} */

void php_phongo_topologyclosedevent_init_ce(INIT_FUNC_ARGS) /* {{{ */
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "MongoDB\\Driver\\Monitoring", "TopologyClosedEvent", php_phongo_topologyclosedevent_me);
	php_phongo_topologyclosedevent_ce                = zend_register_internal_class(&ce);
	php_phongo_topologyclosedevent_ce->create_object = php_phongo_topologyclosedevent_create_object;
	PHONGO_CE_FINAL(php_phongo_topologyclosedevent_ce);
	PHONGO_CE_DISABLE_SERIALIZATION(php_phongo_topologyclosedevent_ce);

	memcpy(&php_phongo_handler_topologyclosedevent, phongo_get_std_object_handlers(), sizeof(zend_object_handlers));
	php_phongo_handler_topologyclosedevent.get_debug_info = php_phongo_topologyclosedevent_get_debug_info;
	php_phongo_handler_topologyclosedevent.free_obj       = php_phongo_topologyclosedevent_free_object;
	php_phongo_handler_topologyclosedevent.offset         = XtOffsetOf(php_phongo_topologyclosedevent_t, std);
} /* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
