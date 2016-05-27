WITH stops7 as (
SELECT p.gid, p.geom, a.st_time,a.end_time,a.time_sum*5,a.traj_count,a.min_time*5, a.max_time*5, (a.time_sum*5/a.traj_count)::float as promedio, s.zona777
FROM parada_util as p, accesibilidad as a, stop_id_frec as s
WHERE a.destiny = s.frec_id AND s.code = p.codigo
    AND st_time=372 AND a.destiny != a.origin
)
SELECT stops7.zona777,AVG(promedio)::float
FROM stops7
GROUP BY stops7.zona777