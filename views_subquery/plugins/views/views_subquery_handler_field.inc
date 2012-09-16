<?php

/**
 * A handler to provide a field that is constructed by the administrator using PHP.
 *
 * @ingroup views_field_handlers
 */
class views_subquery_handler_field extends views_handler_field {

  /**
   * Implements views_object#option_definition().
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['query'] = array('default' => '');
    return $options;
  }

  /**
   * Implements views_handler#options_form().
   */
  function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);

    $form += views_subquery_form_element($this,
      FALSE,
      array('query', t('SQL (Sub Query)'), t('SQL Code to construct the value of this field.'), FALSE)
    );
  }

  /**
   * Implements views_handler_field#query().
   *
   * @see views_subquery_views_pre_execute()
   */
  function query() {
    if ($this->options['query']) {
      // Provide an field alias but don't actually alter the query.
      $this->field_alias = 'views_subquery_' . $this->position;
      // Inform views_subquery_views_pre_execute() to seize control over the query.
      $this->view->views_subquery = TRUE;
      $params = $this->options['group_type'] != 'group' ? array('function' => $this->options['group_type']) : array();
      $this->query->add_field($this->table_alias, $this->options['query'], $this->field_alias, $params);
      $this->add_additional_fields();
    }
  }
}
