<?php

/**
 * Page callback para la vista de administrador de nodos.
 */
function project_manager_view_all_node($node_type = NULL) {
  // Inicializar la variable de salida.
  $output = '';

  // Agregar botones de selección para filtrar por tipo de nodo.
  $output .= '<div style="margin-bottom: 3rem;">';
  $output .= '<a href="' . url('nodes/view/all') . '" class="btn">Show All</a>';
  $output .= '<a href="' . url('nodes/view/project') . '" class="btn">Show Projects</a>';
  $output .= '<a href="' . url('nodes/view/task') . '" class="btn">Show Tasks</a>';
  $output .= '</div>';

  // Construir la consulta para obtener los nodos filtrados por tipo.
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
        ->propertyCondition('status', NODE_PUBLISHED);

  // Agregar filtro por tipo de nodo si se selecciona un tipo específico.
  if ($node_type && $node_type !== 'all') {
    $query->entityCondition('bundle', $node_type);
  }

  // Etiqueta personalizada para filtrar nodos de proyectos y tareas.
  $query->addTag('project_manager_view_all_node');
  $result = $query->execute();

  // Verificar si se encontraron nodos.
  if (!empty($result['node'])) {
    // Construir la tabla HTML para mostrar los nodos.
    $rows = array();
    foreach ($result['node'] as $node) {
      $node = node_load($node->nid); // Cargar el nodo completo.

      // Construir una fila para el nodo.
      $row = array(
        $node->nid,
        check_plain($node->title),
        check_plain($node->type),
        format_date($node->created, 'custom', 'Y-m-d H:i:s'),
      );
      $rows[] = $row;
    }

    // Definir los encabezados de la tabla.
    $header = array(
      'ID',
      'Title',
      'Type',
      'Created',
    );

    // Generar la tabla HTML.
    $output .= theme('table', array('header' => $header, 'rows' => $rows));
  }
  else {
    $output .= '<p>No nodes found.</p>';
  }

  return $output;
}