#include <CGAL/Surface_mesh_default_triangulation_3.h>

// c2t3
#include <CGAL/Complex_2_in_triangulation_3.h>

#include <iostream>  // std::cerr
#include <algorithm> // std::distance

// default triangulation
typedef CGAL::Surface_mesh_default_triangulation_3 Tr;

// c2t3
typedef CGAL::Complex_2_in_triangulation_3<Tr> C2t3;

int main(int , char**)
{
  Tr tr;
  C2t3 c2t3(tr);

  Tr::Vertex_handle v[4];

  v[0]=tr.insert(Tr::Point(0, 0, 0));
  v[1]=tr.insert(Tr::Point(1, 0, 0));
  v[2]=tr.insert(Tr::Point(0, 1, 0));
  v[3]=tr.insert(Tr::Point(0, 0, 1));

  // Set 2 triangles in the complex
  // So it will be 2 facets, and 5 edges in the complex
  for(int i = 0; i < 2; ++i)
  {
    Tr::Cell_handle cell;
    int i1, i2, i3;
    tr.is_facet(v[i+1], v[(i+2)&3], v[(i+3)&3],
                cell,
                i1, i2, i3);
    c2t3.set_in_complex(Tr::Facet(cell, 6 - i1 - i2 - i3));
  }
  
  Tr::size_type number_of_edges = std::distance(c2t3.edges_begin(),
                                                c2t3.edges_end());

  Tr::size_type number_of_facets = std::distance(c2t3.facets_begin(),
                                                 c2t3.facets_end());

  Tr::size_type number_of_boundary_edges = 
    std::distance(c2t3.boundary_edges_begin(),
                  c2t3.boundary_edges_end());

  std::cerr << "Number of edges: " << number_of_edges
            << "\nNumber of facets: " << number_of_facets
            << "\nNumber of boundary edges: " << number_of_boundary_edges
            << "\n";

  // Excepted results:
  CGAL_assertion( number_of_boundary_edges == 4 );
  CGAL_assertion( number_of_edges == 5 );
  CGAL_assertion( number_of_facets == 2 );  

}
