# Feedback Clusters

An explainable, dependency-free Python CLI that groups short feedback comments by topic keywords.

## Usage

```bash
python feedback_clusters.py examples/feedback.json
python -m unittest discover -s tests -v
```

Input: a JSON object with `feedback` (array of strings) and `topics` (mapping of topic names to keyword arrays). Output: total feedback count, topic-to-index mappings and counts. Multiple topics can match one comment; unmatched comments are separately listed.

This uses deterministic substring matching, **not** machine learning, sentiment analysis, or semantic clustering. Topic definitions must be selected carefully to avoid misleading results.
