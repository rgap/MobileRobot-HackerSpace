#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Mesh_triangulation_3.h>
#include <CGAL/Mesh_complex_3_in_triangulation_3.h>
#include <CGAL/Mesh_criteria_3.h>
#include <CGAL/Implicit_mesh_domain_3.h>
#include <CGAL/make_mesh_3.h>

#include <iostream>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::FT FT;
typedef K::Point_3 Point;
typedef FT ( Function)(const Point&);
typedef CGAL::Implicit_mesh_domain_3<Function, K> Mesh_domain;

typedef CGAL::Mesh_triangulation_3<Mesh_domain>::type Tr;
typedef CGAL::Mesh_complex_3_in_triangulation_3<Tr> C3t3;

typedef CGAL::Mesh_criteria_3<Tr> Mesh_criteria;

using namespace CGAL::parameters;

FT sphere_function(const Point& p) {
	return CGAL::squared_distance(p, Point(CGAL::ORIGIN)) - 1;
}

int main() {
	Mesh_domain domain(sphere_function, K::Sphere_3(CGAL::ORIGIN, 2.));
	Mesh_criteria
			criteria(facet_angle = 30, facet_size = 0.1,
					facet_distance = 0.025, cell_radius_edge_ratio = 2,
					cell_size = 0.1);

	C3t3 c3t3 = CGAL::make_mesh_3<C3t3>(domain, criteria);

	cout << "v : " << c3t3.number_of_cells() << endl;
	cout << "e : " << c3t3.number_of_facets() << endl;

	std::ofstream medit_file("out.mesh");
	c3t3.output_to_medit(medit_file);
	return 0;
}
