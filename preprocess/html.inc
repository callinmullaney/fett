<?php

/**
 * @file
 * Preprocess theme_html.
 */

function fett_preprocess_html(&$vars){
  global $theme_key, $language;
  $path = drupal_get_path('theme', $theme_key);
  $path_fett = drupal_get_path('theme', 'fett');

  // Clean up body classes.
  foreach($vars['classes_array'] as $key => &$name){
    if($name == 'page-node-'){
      unset($vars['classes_array'][$key]);
    }
    if($name == 'page-node'){
      unset($vars['classes_array'][$key]);
    }
    elseif(strpos($name, 'page-node-') !== FALSE){
      unset($vars['classes_array'][$key]);
    }
    elseif(strpos($name, 'node-type-') !== FALSE){
      $name = str_replace('node-type','page',$name);
      // unset($vars['classes_array'][$key]);
    }
  }

  // Use a proper attributes array for the html attributes.
  // You can add more attributes to the html elment, for example in a sub-theme you can do this:
  // $vars['html_attributes_array']['xmlns:og'][] = 'http://opengraphprotocol.org/schema/';
  $vars['html_attributes_array']['lang'][] = $language->language;
  $vars['html_attributes_array']['dir'][] = $language->dir;

  // Convert RDF Namespaces into structured data using drupal_attributes.
  $vars['rdf_namespaces'] = array();
  if (function_exists('rdf_get_namespaces')) {
    foreach (rdf_get_namespaces() as $prefix => $uri) {
      $prefixes[] = $prefix . ': ' . $uri;
    }
    $vars['rdf_namespaces_array']['prefix'] = implode(' ', $prefixes);
  }

  // Prevent tags from entering into head title
  $vars['head_title'] = strip_tags(htmlspecialchars_decode($vars['head_title']));

  // nwmatcher
  $script = "\n";
  $script .= '<!--[if lt IE 9]>' . "\n";
  $script .= '<script type="text/javascript" src="//s3.amazonaws.com/nwapi/nwmatcher/nwmatcher-1.2.5-min.js"></script>' . "\n";
  $script .= '<![endif]-->' . "\n";
  $vars['page']['page_bottom']['nwmatcher'] = array(
    '#markup' => $script,
  );

  // selectiviizr
  $script = "\n";
  $script .= '<!--[if (gte IE 6)&(lte IE 8)]>' . "\n";
  $script .= '<script type="text/javascript" src="//cdnjs.cloudflare.com/ajax/libs/selectivizr/1.0.2/selectivizr-min.js"></script>' . "\n";
  $script .= '<![endif]-->' . "\n";
  $vars['page']['page_bottom']['selectivizr'] = array(
    '#markup' => $script,
  );

  // respondjs
  $script = "\n";
  $script .= '<!--[if lt IE 9]>' . "\n";
  $script .= '<script type="text/javascript" src="//cdnjs.cloudflare.com/ajax/libs/respond.js/1.1.0/respond.min.js"></script>' . "\n";
  $script .= '<![endif]-->' . "\n";
  $vars['page']['page_bottom']['respondjs'] = array(
    '#markup' => $script,
  );

  // rem.js
  $script = "\n";
  $script .= '<!--[if lt IE 9]>' . "\n";
  $script .= '<script type="text/javascript" src="' . url($path_fett . '/libraries/rem/rem.min.js', array('absolute' => TRUE)) . '"></script>' . "\n";
  $script .= '<![endif]-->' . "\n";
  $vars['page']['page_bottom']['remjs'] = array(
    '#markup' => $script,
  );
}