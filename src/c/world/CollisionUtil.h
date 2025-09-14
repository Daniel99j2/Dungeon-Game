//
// Created by dj on 24/07/2025.
//

#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Simple_cartesian.h>

typedef CGAL::Simple_cartesian<double> PointType;

static CGAL::Aff_transformation_3<PointType> to_affine(const glm::mat4 &mat) {
	return CGAL::Aff_transformation_3<PointType>(
		mat[0][0], mat[0][1], mat[0][2],
		mat[1][0], mat[1][1], mat[1][2],
		mat[2][0], mat[2][1], mat[2][2],
		mat[3][0], mat[3][1], mat[3][2]
	);
}

using ShapeVariant = std::variant<
	CGAL::Triangle_3<PointType>,
	CGAL::Iso_cuboid_3<PointType>,
	CGAL::Sphere_3<PointType>
>;

class CollisionUtil {
public:
	static bool colliding_with(const ShapeVariant &shapeA, const glm::mat4 &transformA,
							   const ShapeVariant &shapeB, const glm::mat4 &transformB) {
		auto transformedA = transform_shape(shapeA, transformA);
		auto transformedB = transform_shape(shapeB, transformB);
		return std::visit([](const auto &sa, const auto &sb) {
			return CGAL::do_intersect(sa, sb);
		}, transformedA, transformedB);
	}

	static ShapeVariant transform_shape(const ShapeVariant &shape, const glm::mat4 &transform) {
		return std::visit([&]<typename T0>(const T0 &s) -> ShapeVariant {
			using T = std::decay_t<T0>;

			if constexpr (std::is_same_v<T, CGAL::Triangle_3<PointType> >) {
				return s.transform(to_affine(transform));
			}
			else if constexpr (std::is_same_v<T, CGAL::Sphere_3<PointType> >) {
				return static_cast<CGAL::Sphere_3<PointType>>(s).orthogonal_transform(to_affine(transform));
			}
			else if constexpr (std::is_same_v<T, CGAL::Iso_cuboid_3<PointType> >) {
				return transform_cuboid(s, to_affine(transform));
			}
			throw std::runtime_error("Invalid shape type");
		}, shape);
	}

	template<typename Kernel>
	static CGAL::Iso_cuboid_3<Kernel> transform_cuboid(const CGAL::Iso_cuboid_3<Kernel>& cuboid, const CGAL::Aff_transformation_3<Kernel>& transform) {
		using Point = typename Kernel::Point_3;
		std::vector<Point> transformed_points;

		for (int dx = 0; dx <= 1; ++dx) {
			for (int dy = 0; dy <= 1; ++dy) {
				for (int dz = 0; dz <= 1; ++dz) {
					Point p(
						dx ? cuboid.xmax() : cuboid.xmin(),
						dy ? cuboid.ymax() : cuboid.ymin(),
						dz ? cuboid.zmax() : cuboid.zmin()
					);
					transformed_points.push_back(transform(p));
				}
			}
		}

		double min_x = transformed_points[0].x(), max_x = min_x;
		double min_y = transformed_points[0].y(), max_y = min_y;
		double min_z = transformed_points[0].z(), max_z = min_z;

		for (const Point& p : transformed_points) {
			min_x = std::min(min_x, p.x());
			max_x = std::max(max_x, p.x());
			min_y = std::min(min_y, p.y());
			max_y = std::max(max_y, p.y());
			min_z = std::min(min_z, p.z());
			max_z = std::max(max_z, p.z());
		}

		return CGAL::Iso_cuboid_3<Kernel>(min_x, min_y, min_z, max_x, max_y, max_z);
	}
};

class CollisionMap {
public:
	std::vector<ShapeVariant> collisionParts;
	CGAL::Iso_cuboid_3<PointType> largeBox;
};

