<?php

/**
 * @file
 * Provide views handlers and plugins that allow usage of PHP.
 */

/**
 * Implements hook_views_data().
 */
function views_subquery_views_data() {
  $data['views']['subquery'] = array(
    'title' => t('Sub Query'),
    'help' => t('Use sub query.'),
    'area' => array(
      'help' => t('Use sub query to construct the output of an area.'),
      'handler' => 'views_subquery_handler_area',
    ),
    'field' => array(
      'help' => t('Use sub query to construct the output of a field.'),
      'handler' => 'views_subquery_handler_field',
    ),
    'filter' => array(
      'help' => t('Use sub query to filter the result of the view.'),
      'handler' => 'views_subquery_handler_filter',
    ),
    'sort' => array(
      'help' => t('Use sub query to sort the result of the view.'),
      'handler' => 'views_subquery_handler_sort',
    ),
  );
  return $data;
}

/**
 * Implements hook_views_plugins().
 */
function views_subquery_views_plugins() {
  $plugins = array(
    'access' => array(
      'subquery' => array(
        'title' => t('Sub Query'),
        'help' => t('Use PHP code to grant access.'),
        'handler' => 'views_subquery_plugin_access',
        'uses options' => TRUE,
      ),
    ),
    'cache' => array(
      'subquery' => array(
        'title' => t('Sub Query'),
        'help' => t('Use PHP code to determine whether a should be cached.'),
        'handler' => 'views_subquery_plugin_cache',
        'uses options' => TRUE,
      ),
    ),
  );
  return $plugins;
}
