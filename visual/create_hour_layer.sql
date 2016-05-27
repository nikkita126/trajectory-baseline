SELECT p.gid, p.geom, a.st_time,a.end_time,a.time_sum*5 as time_sum,a.traj_count,a.min_time*5 as min_time, a.max_time*5 as max_time, ((a.time_sum*5)::float/a.traj_count::float)::float as promedio, s.zona777
FROM parada_util as p, accesibilidad as a, stop_id_frec as s
WHERE a.destiny = s.frec_id AND s.code = p.codigo
    AND st_time=384 AND a.destiny != a.origin