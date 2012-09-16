<?php

/**
 * A handler to sort a view using PHP defined by the administrator.
 *
 * @ingroup views_sort_handlers
 */
class views_subquery_handler_sort extends views_handler_sort {

  /**
   * Implements views_object#option_definition().
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['query'] = array('default' => '');
    return $options;
  }

  /**
   * Implements views_handler#option_definition().
   */
  function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);

    $form += views_subquery_form_element(
      $this,
      FALSE,
      array('query', t('SQL'), t('SQL for sorting. SQL code or one of the fields at FIELDS section (Changing Views Setting as ticking "Show the SQL query" checkbox will lead you what you can put).'), FALSE)
    );
  }

  /**
   * Implements views_handler_sort#query().
   */
  function query() {
    // Inform views_subquery_views_pre_execute() to seize control over the query.
    if ($this->options['query']) {
      $this->view->views_subquery = TRUE;
      $this->query->add_orderby($this->table_alias, NULL, $this->options['order'], $this->options['query']);
    }
  }
}
