
/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2017 Phalcon Team (https://phalconphp.com)          |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file LICENSE.txt.                             |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 +------------------------------------------------------------------------+
 */

namespace Phalcon\Mvc\Model;

use Phalcon\DiInterface;

/**
 * Phalcon\Mvc\Model\CriteriaInterface
 *
 * Interface for Phalcon\Mvc\Model\Criteria
 */
interface CriteriaInterface
{

	/**
	 * Set a model on which the query will be executed
	 */
	public function setModelName(string! modelName) -> <CriteriaInterface>;

	/**
	 * Returns an internal model name on which the criteria will be applied
	 */
	public function getModelName() -> string;

	/**
	 * Sets the bound parameters in the criteria
	 * This method replaces all previously set bound parameters
	 */
	public function bind(array! bindParams, boolean merge = false) -> <CriteriaInterface>;

	/**
	 * Sets the bind types in the criteria
	 * This method replaces all previously set bound parameters
	 */
	public function bindTypes(array! bindTypes) -> <CriteriaInterface>;

	/**
	 * Sets the conditions parameter in the criteria
	 */
	public function where(string! conditions, var bindParams = null, var bindTypes = null) -> <CriteriaInterface>;

	/**
	 * Adds the conditions parameter to the criteria
	 */
	public function conditions(string! conditions) -> <CriteriaInterface>;

	/**
	 * Adds the order-by parameter to the criteria
	 */
	public function orderBy(string! orderColumns) -> <CriteriaInterface>;

	/**
	 * Sets the limit parameter to the criteria
	 *
	 * @param int offset
	 */
	public function limit(int limit, var offset = null) -> <CriteriaInterface>;

	/**
	 * Sets the "for_update" parameter to the criteria
	 */
	public function forUpdate(boolean forUpdate = true) -> <CriteriaInterface>;

	/**
	 * Sets the "shared_lock" parameter to the criteria
	 */
	public function sharedLock(boolean sharedLock = true) -> <CriteriaInterface>;

	/**
	 * Appends a condition to the current conditions using an AND operator
	 *
	 * @param array bindParams
	 * @param array bindTypes
	 */
	public function andWhere(string! conditions, var bindParams = null, var bindTypes = null) -> <CriteriaInterface>;

	/**
	 * Appends a condition to the current conditions using an OR operator
	 *
	 * @param array bindParams
	 * @param array bindTypes
	 */
	public function orWhere(string! conditions, var bindParams = null, var bindTypes = null) -> <CriteriaInterface>;

	/**
	 * Appends a BETWEEN condition to the current conditions
	 *
	 *<code>
	 * $criteria->betweenWhere("price", 100.25, 200.50);
	 *</code>
	 *
	 * @param mixed minimum
	 * @param mixed maximum
	 */
	public function betweenWhere(string! expr, var minimum, var maximum) -> <CriteriaInterface>;

	/**
	 * Appends a NOT BETWEEN condition to the current conditions
	 *
	 *<code>
	 * $criteria->notBetweenWhere("price", 100.25, 200.50);
	 *</code>
	 *
	 * @param mixed minimum
	 * @param mixed maximum
	 */
	public function notBetweenWhere(string! expr, var minimum, var maximum) -> <CriteriaInterface>;

	/**
	 * Appends an IN condition to the current conditions
	 *
	 *<code>
	 * $criteria->inWhere("id", [1, 2, 3]);
	 *</code>
	 */
	public function inWhere(string! expr, array! values) -> <CriteriaInterface>;

	/**
	 * Appends a NOT IN condition to the current conditions
	 *
	 *<code>
	 * $criteria->notInWhere("id", [1, 2, 3]);
	 *</code>
	 */
	public function notInWhere(string! expr, array! values) -> <CriteriaInterface>;

	/**
	 * Returns the conditions parameter in the criteria
	 *
	 * @return string|null
	 */
	public function getWhere();

	/**
	 * Returns the conditions parameter in the criteria
	 *
	 * @return string|null
	 */
	public function getConditions();

	/**
	 * Returns the limit parameter in the criteria, which will be
	 * an integer if limit was set without an offset,
	 * an array with 'number' and 'offset' keys if an offset was set with the limit,
	 * or null if limit has not been set.
	 *
	 * @return int|array|null
	 */
	public function getLimit();

	/**
	 * Returns the order parameter in the criteria
	 *
	 * @return string|null
	 */
	public function getOrderBy();

	/**
	 * Returns all the parameters defined in the criteria
	 */
	public function getParams() -> array;

	/**
	 * Executes a find using the parameters built with the criteria
	 */
	public function execute() -> <ResultsetInterface>;

}
