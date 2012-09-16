<?php

/**
 * A handler to filter a view using PHP defined by the administrator.
 *
 * @ingroup views_filter_handlers
 */
class views_subquery_handler_filter extends views_handler_filter {

  protected $php_static_variable = NULL;

  /**
   * Implements views_handler#can_expose().
   */
  function can_expose() { return FALSE; }

  /**
   * Implements views_object#admin_summary().
   */
  function admin_summary() {
    return t('Sub Query');
  }

  /**
   * Implements views_object#option_definition().
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['where'] = array('default' => '');
    $options['having'] = array('default' => '');
    return $options;
  }

  /**
   * Implements views_handler#option_definition().
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form += views_subquery_form_element($this,
      FALSE,
      array('where', t('WHERE'), t('Put whatever you want for WHERE statement part.'), FALSE)
    );
    $form += views_subquery_form_element($this,
      FALSE,
      array('having', t('HAVING'), t('Put whatever you want for HAVING statement part.'), FALSE)
    );
  }

  /**
   * Implements views_handler_filter#query().
   */
  function query() {
    // Inform views_subquery_views_pre_execute() to seize control over the query.
    if ($this->options['where']) {
      $this->view->views_subquery = TRUE;
      $this->query->add_where_expression(0, $this->options['where']);
    }
    if ($this->options['having']) {
      $this->view->views_subquery = TRUE;
      $this->query->add_having_expression(0, $this->options['having']);
    }
  }
}
